#include "animatable.h"

animatable::animatable(SDL_Texture* texture_map, size_t frames, size_t offset, size_t width, size_t height, size_t timer) :
 texture_map(texture_map), frames(frames), offset(offset), width(width), height(height), curr_frame(0), timer(timer), curr_time(0) {
}

animatable::animatable() {
}

void animatable::update() {
    if(this->curr_time == this->timer) {
        this->curr_frame++;
        if(this->curr_frame >= this->frames) this->curr_frame = 0;
        this->curr_time = 0;
    } else {
        this->curr_time++;
    }
}
void animatable::render(SDL_Rect screen_pos, SDL_Renderer* renderer) {
    SDL_Rect tex_pos = SDL_Rect{(int)(this->offset * this->curr_frame), 0, (int)this->width, (int)this->height};
    SDL_RenderCopy(renderer, this->texture_map, &tex_pos, &screen_pos);
}

animatable::~animatable() {
}