#include "player.h"

player::player(int start_x, int start_y, SDL_Texture* texture_map, size_t timer) :
    x(start_x), y(start_y), animatable{texture_map, 8, 32, 32, 32, timer} {
}

player::player() : animatable{} {

}

void player::render(float scale, SDL_Renderer* renderer, const size_t screen_height) {
    SDL_Rect screen_pos = SDL_Rect{(int)(this->x - this -> width * scale / 2),
                                   (int)((screen_height - this->y) - this -> height * scale / 2),
                                   (int)(this->width * scale),
                                   (int)(this->height * scale)};
    this->animatable::render(screen_pos, renderer);
}

player::~player() {
}