#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

SDL_Texture* load_texture_from_file(const std::string& path, SDL_Renderer* renderer);