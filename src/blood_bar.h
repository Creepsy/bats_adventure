#pragma once

#include <SDL2/SDL.h>

class blood_bar
{
private:
    int x, y;
    SDL_Texture* border;
    SDL_Texture* infill;
    double percentage;
public:
    blood_bar(int x, int y, SDL_Texture* border, SDL_Texture* infill);
    blood_bar();
    void render(SDL_Renderer* renderer, float scale);
    double get_percentage();
    void set_percentage(double value);
    ~blood_bar();
};


