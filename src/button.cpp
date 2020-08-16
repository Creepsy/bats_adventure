#include "button.h"

button::button(SDL_Rect hitbox, SDL_Texture* texture, std::string title, TTF_Font* font) : hitbox(hitbox), texture(texture), title(title), font(font) {
}

void button::render(SDL_Renderer* renderer, double scale) {
    SDL_RenderCopy(renderer, this->texture, nullptr, &this->hitbox);

    SDL_Color black = SDL_Color{0, 0, 0};


    SDL_Surface* surface_message = TTF_RenderText_Solid(this->font, this->title.c_str(), black);
    SDL_Texture* texture_message = SDL_CreateTextureFromSurface(renderer, surface_message);

    int w, h;
    TTF_SizeText(this->font, title.c_str(), &w, &h);
    SDL_Rect message_rect = SDL_Rect{this->hitbox.x + this-> hitbox.w / 2 - w / 2, this->hitbox.y + this->hitbox.h / 2 - h / 2, w, h};


    SDL_RenderCopy(renderer, texture_message, nullptr, &message_rect);

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(texture_message);
}

void button::set_title(std::string title) {
    this->title = title;
}

bool button::click(int x, int y) {
    if(x >= this->hitbox.x && x <= this->hitbox.x + this->hitbox.w) {
        if(y >= this->hitbox.y && y <= this->hitbox.y + this->hitbox.h) {
            return true;
        }
    }
    return false;
}

std::string button::get_title() {
    return this->title;
}

button::~button()
{
}