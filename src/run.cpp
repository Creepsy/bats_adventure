#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main() {
    SDL_Window* window = nullptr;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    window = SDL_CreateWindow("Bat's Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 512, SDL_WINDOW_SHOWN);

    if(!window) return 1;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return 1;
    SDL_Surface* test = IMG_Load("textures/tilemap/grass_0.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, test);
    SDL_FreeSurface(test);

    char r = 0, g = 0, b = 0;

    bool running = true;

    SDL_Rect target;
    target.x = 512;
    target.y = 128;
    target.w = 64;
    target.h = 64;

    while (running) {
        SDL_RenderCopy(renderer, tex, nullptr, &target);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        r++;
        g++;
        b++;
        if(r == 255) r = 0;
        if(g == 120) g = 0;
        if(b == 25) b = 0;

        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) running = false;
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        SDL_RenderClear(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(tex);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}