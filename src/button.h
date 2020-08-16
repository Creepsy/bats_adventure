#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class button {
    private:
        SDL_Rect hitbox;
        SDL_Texture* texture;
        TTF_Font* font;
        std::string title;
    public:
        button(SDL_Rect hitbox, SDL_Texture* texture, std::string title, TTF_Font* font);
        void render(SDL_Renderer* renderer, double scale);
        bool click(int x, int y);
        std::string get_title();
        void set_title(std::string title);
        ~button();
};