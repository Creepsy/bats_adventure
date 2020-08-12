#include "texture_loader.h"

SDL_Texture* load_texture_from_file(const std::string& path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* texure = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texure;
}