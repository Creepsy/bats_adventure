#include "player.h"

player::player(float start_x, float start_y, SDL_Texture* texture_map, size_t timer) :
    x(start_x), y(start_y), animatable{texture_map, 8, 32, 32, 32, timer} {
}

player::player() : animatable{} {

}

void player::render(float scale, SDL_Renderer* renderer, const size_t screen_height) {
    SDL_Rect screen_pos = SDL_Rect{(int)(this->x - this -> width * scale / 2),
                                   (int)((screen_height - this->y) - this -> height * scale / 2),
                                   (int)(this->width * scale),
                                   (int)(this->height * scale)};
    this->animatable::render(screen_pos, renderer, -this->velocity_y * 10);
}

void player::add_force(float fx, float fy) {
    this->velocity_x += fx;
    this->velocity_y += fy;

    if(this->velocity_y > 6) this->velocity_y = 6;
}
void player::move(const size_t screen_width, const size_t screen_height) {
    this->x += this->velocity_x;
    this->y += this->velocity_y;

    if(this->x < 0) {
        this->x = 0;
        this->velocity_x = 0;
    } 
    if(this->y < 0) {
        this->y = 0;
        this->velocity_y = 0;
    } 

    if(this->x > screen_width) {
        this->x = screen_width;
        this->velocity_x = 0;
    } 
    if(this->y > screen_height) {
        this->y = screen_height;
        this->velocity_y = 0;
    }
}

bool player::does_collide(SDL_Rect tile, const size_t screen_height) {   
    int real_y = screen_height - this->y; 
    return this->x + this->width / 4 < tile.x + tile.w && this->x + this->width / 4 * 3 > tile.x && real_y + this->height / 4 < tile.y + tile.h && real_y + this->height / 4 * 3 > tile.y;
}

player::~player() {
}