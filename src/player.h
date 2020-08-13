#pragma once

#include "animatable.h"

class player : public animatable
{
private:
    float x, y;
    float velocity_x, velocity_y;
public:
    player(float start_x, float start_y, SDL_Texture* texture_map, size_t timer = 0);
    player();
    void render(float scale, SDL_Renderer* renderer, const size_t screen_height);
    void add_force(float fx, float fy);
    void move(const size_t screen_width, const size_t screen_height);
    ~player();
};