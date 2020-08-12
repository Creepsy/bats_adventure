#include "game.h"

game::game(const size_t width, const size_t height, const std::string& title) : width(width), height(height), title(title), running(false) {
}

bool game::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);

    if(!window) return false;
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;

    this->running = true;
    this->test = load_texture_from_file("textures/tilemap/grass_0.png", this->renderer);
    this->init_grid();

    return true;
}

void game::init_grid() {
    for(int w = 0; w < this->width / 32 + 2; w++){
        std::vector<std::pair<int, int>> row;
        row.push_back(std::make_pair(w - 1, 0));
        this->map.push_back(row);
    }
}

void game::run() {
    while(this->running) {
        SDL_RenderClear(this->renderer);

        for(std::vector<std::pair<int, int>>& row : this->map) {
            for(std::pair<int, int>& tile : row) {
                SDL_Rect pos = SDL_Rect{tile.first * 32, (int)this->height - tile.second * 32 - 32, 32, 32};
                SDL_RenderCopy(this->renderer, this->test, nullptr, &pos);
            }
        }

        SDL_RenderPresent(renderer);

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            this->handle_events(event);
        }
        SDL_Delay(100);
    }
}

game::~game() {
    SDL_DestroyTexture(this->test);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void game::handle_events(SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE) this->running = false;
            break;
        case SDL_QUIT:
            this->running = false;
            break;
    }
}