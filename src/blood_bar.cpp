#include "blood_bar.h"

#include <iostream>

blood_bar::blood_bar(int x, int y, SDL_Texture* border, SDL_Texture* infill) :
 x(x), y(y), percentage(0), border(border), infill(infill) {
}

blood_bar::blood_bar(){

}

double blood_bar::get_percentage() {
    return this->percentage;
}

void blood_bar::set_percentage(double value) {
    this->percentage = value;
    if(this->percentage < 0) this->percentage = 0;
    if(this->percentage > 1) this->percentage = 1;
}

void blood_bar::render(SDL_Renderer* renderer, float scale) {
    SDL_Rect border = SDL_Rect{this->x, this->y, (int)(128 * scale), (int)(32 * scale)};
    SDL_RenderCopy(renderer, this->border, nullptr, &border);

    SDL_Rect infill_src = SDL_Rect{0, 0, (int)(98 * this->percentage), 32};
    SDL_Rect infill_tar = SDL_Rect{this->x + (int)(17 * scale), this->y, (int)(98 * this->percentage * scale), (int)(32 * scale)};
    SDL_RenderCopy(renderer, this->infill, &infill_src, &infill_tar);
}

blood_bar::~blood_bar()
{
}