#include "game.h"

#include <iostream>

game::game(const size_t width, const size_t height, const std::string& title) : 
    window_width(width), window_height(height), title(title), running(false), game_speed(0.05), bat{position{-100, -100}, nullptr, 0, 0} {
}

bool game::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->window_width, this->window_height, SDL_WINDOW_SHOWN);

    if(!window) return false;
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;

    this->running = true;

    this->load_textures();
    this->init_grid();

    this->bat = player{position{128, 256}, this->textures[28], 500, 4};
    this->bar = blood_bar{0, 0, this->textures[30], this->textures[31]};
    this->bar.set_percentage(this->bat.get_blood() / this->bat.get_max_blood());

  //  this->hop = grass_hopper{position{1000, 256}, this->textures[34], 2.25};

 //   this->enemies.push_back(snake{position{512, 256}, this->textures[32], this->textures[33], 256, 8});

    return true;
}

void game::run() {
    while(this->running) {
        SDL_RenderClear(this->renderer);

        SDL_RenderCopy(this->renderer, this->textures[29], nullptr, nullptr);

        for(int i = 0; i < this->enemies.size(); i++) {
            enemy* e = this->enemies.at(i);
            e->add_force(position{0, -0.1});
            if(dynamic_cast<snake*>(e)) {
                if(e->can_see(this->bat.get_position())) e->on_player_spot(this->bat);
                if(e->does_collide(this->bat.get_collider(2), 2)) e->on_player_collision(this->bat);
            } else {
                if(e->does_collide(this->bat.get_collider(2), 1)) {
                    e->on_player_collision(this->bat);
                    delete e;
                    this->enemies.erase(this->enemies.begin() + i);
                    i--;
                }
            }
        }

        /*for(snake& s : this->enemies) {
            s.add_force(position{0, -0.1});

            if(s.can_see(this->bat.get_position())) {
                s.on_player_spot(this->bat);
            }

            if(s.does_collide(this->bat.get_collider(2), 2)) {
                s.on_player_collision(this->bat);
            }
        }
        if(this->hop.does_collide(this->bat.get_collider(2), 1)) this->hop.on_player_collision(this->bat);
        this->hop.add_force(position{0, -0.1});
*/
        for(int i = 0; i < this->map.size(); i++) {
            std::vector<tile>& row = this->map.at(i);
            if(row.at(0).x < -1) {
                this->map.erase(this->map.begin());
                i--;
                this->generate_row();
                continue;
            }
            bool reset = false;
            for(tile& t : row) {
                SDL_Rect pos = SDL_Rect{(int)(t.x * 32), (int)(this->window_height - t.y * 32 - 32), 33, 32};
                if(this->bat.does_collide(pos, 2) || this->bar.get_percentage() == 0) {
                    this->bat.on_tile_collision();
                    SDL_Delay(1500);

                    this->init_grid();
                    this->bat = player{position{128, 256}, this->textures[28], 500, 4};
                    this->bar.set_percentage(this->bat.get_blood() / this->bat.get_max_blood());
                    reset = true;
                    break;
                }

                for(enemy* e : this->enemies) {
                    if(dynamic_cast<snake*>(e)) {
                        if(e->does_collide(pos, 2)) e->on_tile_collision();
                    } else {
                        if(e->does_collide(pos, 1)) e->on_tile_collision();
                    }
                }
               /* for(snake& s : this-> enemies) {
                    if(s.does_collide(pos, 2)) {
                        s.on_tile_collision();
                    }
                }
                if(this->hop.does_collide(pos, 1)) {
                    this->hop.on_tile_collision();
                } */
                if(reset) break;

                SDL_RenderCopy(this->renderer, this->textures[t.texture_id], nullptr, &pos);
                t.x -= this->game_speed;
            }
            if(reset) break;
        }
       /* for(int i = 0; i < this->enemies.size(); i++) {
            snake& s = this->enemies.at(i);

            if(s.get_position().x < -100 || s.get_position().y < -100) {
                this->enemies.erase(this->enemies.begin() + i);
                i--;
                continue;
            }

            s.update();
            SDL_Rect col = s.get_collider(2);
            SDL_RenderDrawRect(this->renderer, &col);


            position snake_pos = s.get_position();
            snake_pos.x -= this->game_speed * 32;
            s.set_position(snake_pos);


            s.render(this->renderer, 2);
        }
        this->hop.update();
        position hop_pos = this->hop.get_position();
        hop_pos.x -= this->game_speed * 32;
        this->hop.set_position(hop_pos);

        SDL_Rect hop_col = this->hop.get_collider(1);
        SDL_RenderDrawRect(this->renderer, &hop_col);

        this->hop.render(this->renderer, 1);
*/
        for(int i = 0; i < this->enemies.size(); i++) {
            enemy* e = this->enemies.at(i);
            if(e->get_position().x < -100 || e->get_position().y < -100) {
                delete e;
                this->enemies.erase(this->enemies.begin() + i);
                i--;
                continue;
            }

            e->update();

            position pos = e->get_position();
            pos.x -= this->game_speed * 32;
            e->set_position(pos);


            if(dynamic_cast<snake*>(e)) {
                e->render(this->renderer, 2);
            } else {
                e->render(this->renderer, 1);
            }

        }
       // this->bat.damage(0.25); <-- Dont fiorget to uncomment this!
        this->bat.add_force(position{0, -0.1});
        this->bat.update();
        this->bat.render(this->renderer, 2);

        SDL_Rect col = bat.get_collider(2);
        SDL_RenderDrawRect(this->renderer, &col);

        this->bar.set_percentage(this->bat.get_blood() / this->bat.get_max_blood());
        this->bar.render(this->renderer, 1);
    
        SDL_RenderPresent(renderer);

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            this->handle_events(event);
        }
        SDL_Delay(10);
    }
}

game::~game() {
    for(enemy* e : this->enemies) delete e;
    for(SDL_Texture* t : this->textures) SDL_DestroyTexture(t);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void game::handle_events(SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE) this->running = false;
            if(event.key.keysym.sym == SDLK_SPACE) {
                if(this->bat.get_blood() > this->bat.get_max_blood() * 0.6) {
                    double excess = this->bat.get_blood() - this->bat.get_max_blood() * 0.6;
                    double max_excess = this->bat.get_max_blood() * 0.4;
                    double slow = (1 - excess / max_excess < 0.4) ? 0.4 : 1 - excess / max_excess;
                    std::cout << slow << std::endl;
                    this->bat.add_force(position{0, 8 * slow});
                } else {
                    this->bat.add_force(position{0, 8});
                }
            }
            break;
        case SDL_QUIT:
            this->running = false;
            break;
    }
}

void game::generate_row() {
    if(this->next_change == 0) {
        this->next_change = rand_int(1, this ->max_change_time);

        this->current_change = 0;

        do {
            this->current_change = rand_int(-this->max_change, this->max_change);
        } while(/*this->current_change == 0 ||*/ this->current_height + this->current_change < 0 || this->current_height + this->current_change > this->max_height);
    } else {
        this->next_change--;
        this->current_height += this->current_change;

        if(this->current_height < 0) this->current_height = 0;
        if(this->current_height > this->max_height) this->current_height = this->max_height;
    }

    std::vector<tile> row{this->window_height / 32, tile{-1, -1, 0}};
    for(int i = 0; i < this->current_height; i++) {
        row.at(i) = tile{this->map.back().at(0).x + 1, (float)i};
    }
    row.at(this->current_height) = tile{this->map.back().at(0).x + 1, (float)this->current_height};
    this->map.push_back(row);

    for(int x = this->map.size() - 2; x < this->map.size(); x++) {
        for(int y = 0; y < this->map.at(x).size(); y++) {
            this->map.at(x).at(y).texture_id = this->get_texture_id(x, y);
        }
    }

    if((double)rand() / RAND_MAX < this->spawn_entity && next_change == 0) {
        if((double)rand() / RAND_MAX < this->is_snake) {
            this->enemies.push_back(new snake{position{row.at(current_height).x * 32, row.at(current_height).y * 32 + 128}, this->textures[32], this->textures[33], (double)rand_int(256, 384), (double)rand_int(7, 9)});
        } else {
            this->enemies.push_back(new grass_hopper{position{row.at(current_height).x * 32, row.at(current_height).y * 32 + 128}, this->textures[34], (double)rand_int(4, 7)});
        }
    }
}

void game::init_grid() {
    for(enemy* e : this->enemies) delete e;
    this->enemies.clear();
    this->map.clear();
    this->current_change = 0;
    this->current_height = 0;
    this->next_change = 0;

    for(int w = 0; w < this->window_width / 32 + 2; w++){
        std::vector<tile> row{this->window_height / 32, tile{-1, -1, 0}};
        row.at(this->current_height) = tile{(float)w - 1, (float)this->current_height};
        this->map.push_back(row);
    }

    for(int x = 0; x < this->map.size(); x++) {
        for(int y = 0; y < this->map.at(x).size(); y++) {
            this->map.at(x).at(y).texture_id = this->get_texture_id(x, y);
        }
    }
}

int game::get_texture_id(int x, int y) {
    //grass
    if(this->is_occupied(x + 1, y) && this->is_occupied(x - 1, y) && !this->is_occupied(x, y + 1)) {
        return rand_int(1, 6);
    }

    //corner_right
    if(!this->is_occupied(x + 1, y) && this->is_occupied(x - 1, y) && !this->is_occupied(x, y + 1)) {
        return rand_int(11, 16);
    }

    //corner_left
    if(this->is_occupied(x + 1, y) && !this->is_occupied(x - 1, y) && !this->is_occupied(x, y + 1)) {
        return rand_int(6, 11);
    }

    //wall left
    if(!this->is_occupied(x - 1, y) && this->is_occupied(x, y + 1)) {
        return rand_int(16, 21);
    }

    //wall right
    if(!this->is_occupied(x + 1, y) && this->is_occupied(x, y + 1)) {
        return rand_int(21, 26);
    }

    //wall connect left
    if(!this->is_occupied(x + 1, y + 1) && this->is_occupied(x, y + 1) && this->is_occupied(x + 1, y)) {
        return 26;
    }

    //wall connect right
    if(!this->is_occupied(x - 1, y + 1) && this->is_occupied(x, y + 1) && this->is_occupied(x - 1, y)) {
        return 27;
    }

    return 0;
}

void game::load_textures() {
    this->textures.push_back(load_texture_from_file("textures/tilemap/dirt.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_0.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_1.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_2.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_3.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_4.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_left_0.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_left_1.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_left_2.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_left_3.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_left_4.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_right_0.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_right_1.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_right_2.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_right_3.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/grass_side_right_4.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_left_0.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_left_1.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_left_2.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_left_3.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_left_4.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_right_0.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_right_1.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_right_2.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_right_3.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_right_4.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_connect_left.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/tilemap/wall_connect_right.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/bat.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/background.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/blood_bar.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/blood_bar_fill.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/snake_idle.png", this->renderer));
    this->textures.push_back(load_texture_from_file("textures/snake_jumping.png", this->renderer));

    this->textures.push_back(load_texture_from_file("textures/grass_hopper.png", this->renderer));
}

bool game::is_occupied(int x, int y) {
    try
    {
        tile& t = this -> map.at(x).at(y);
        if(t.y < 0) return false;
        return true;
    }
    catch(const std::out_of_range& e)
    {
        return false;
    }
    
}