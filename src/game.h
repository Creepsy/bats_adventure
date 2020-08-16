#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "utils.h"
#include "player.h"
#include "blood_bar.h"
#include "snake.h"
#include "grass_hopper.h"

class game {
    private:
        long score;

        int current_height = 0;
        int current_change = 0;
        int max_height = 7;
        int max_change = 2;
        int max_change_time = 3;
        int next_change = 0;

        double spawn_entity = 0.75;
        double is_snake = 0.4;

        float game_speed;

        const size_t window_width, window_height;
        const std::string title;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool running;

        std::vector<SDL_Texture*> textures;
        TTF_Font* font;

        std::vector<std::vector<tile>> map;

        player bat;
        blood_bar bar;
        std::vector<enemy*> enemies;

        void handle_events(SDL_Event& event);
        void init_grid();
        void generate_row();
        int get_texture_id(int x, int y);
        void load_textures();
        bool is_occupied(int x, int y);
    public:
        game(const size_t width, const size_t height, const std::string& title);
        bool init();
        void run();
        ~game();
};
