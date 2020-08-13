#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class animatable {
private:
    SDL_Texture* texture_map;
    size_t frames, offset, width, height;
    size_t curr_frame;
    size_t timer;
    size_t curr_time;
public:
    animatable(SDL_Texture* texture_map, size_t frames, size_t offset, size_t width, size_t height, size_t timer = 0);
    animatable();
    void update();
    void render(SDL_Rect screen_pos, SDL_Renderer* renderer);
    ~animatable();
};


