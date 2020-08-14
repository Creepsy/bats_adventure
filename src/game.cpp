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

    return true;
}

void game::run() {
    while(this->running) {
        SDL_RenderClear(this->renderer);

        SDL_RenderCopy(this->renderer, this->textures[29], nullptr, nullptr);

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
                if(this->bat.does_collide(pos) || this->bar.get_percentage() == 0) {
                    this->bat.on_tile_collision();
                    SDL_Delay(1500);

                    this->init_grid();
                    this->bat = player{position{128, 256}, this->textures[28], 500, 4};
                    this->bar.set_percentage(this->bat.get_blood() / this->bat.get_max_blood());
                    reset = true;
                    break;
                }
                if(reset) break;

                SDL_RenderCopy(this->renderer, this->textures[t.texture_id], nullptr, &pos);
                t.x -= this->game_speed;
            }
        }
        this->bat.damage(0.5);
        this->bat.add_force(position{0, -0.1});
        this->bat.update();
        this->bat.render(this->renderer, 2);

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
    for(SDL_Texture* t : this->textures) SDL_DestroyTexture(t);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void game::handle_events(SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE) this->running = false;
            if(event.key.keysym.sym == SDLK_SPACE) this->bat.add_force(position{0, 8});
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
        } while(this->current_change == 0 || this->current_height + this->current_change < 0 || this->current_height + this->current_change > this->max_height);
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
}

void game::init_grid() {
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