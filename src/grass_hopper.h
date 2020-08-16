#pragma once

#include "entity_types.h"
#include "player.h"

class grass_hopper : public enemy {
    private:
        SDL_Texture* tex;
        double jump_force;
    public:
        grass_hopper (position pos, SDL_Texture* tex, double jump_force);
        void on_player_collision(entity& p, double speed_multiplier) override;
        void on_player_spot(entity& p, double speed_multiplier) override;
        void render(SDL_Renderer* renderer, double scale) override;
        SDL_Rect get_collider(double scale) override;
        void on_tile_collision(double speed_multiplier) override;
        ~grass_hopper();
};