#pragma once

#include "animatable.h"

class player : public animatable
{
private:
    int x, y;
public:
    player(int start_x, int start_y, SDL_Texture* texture_map, size_t timer = 0);
    player();
    void render(float scale, SDL_Renderer* renderer, const size_t screen_height);
    ~player();
};