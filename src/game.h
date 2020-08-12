#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

#include "utils.h"

class game {
    private:
        const size_t width, height;
        const std::string title;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool running;

        SDL_Texture* test = nullptr;

        std::vector<std::vector<std::pair<int, int>>> map;

        void handle_events(SDL_Event& event);
        void init_grid();
    public:
        game(const size_t width, const size_t height, const std::string& title);
        bool init();
        void run();
        ~game();
};
