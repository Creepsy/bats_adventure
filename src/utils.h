#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

struct tile {
    float x = -1;
    float y = -1;
    int texture_id = 0;
};

SDL_Texture* load_texture_from_file(const std::string& path, SDL_Renderer* renderer);
int rand_int(int start, int end);