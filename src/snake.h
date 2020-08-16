#pragma once

#include "entity_types.h"
#include "player.h"

class snake : public enemy {
    private:
        SDL_Texture* idle;
        SDL_Texture* jump;
        bool attacking;
        bool damaged;
        double jump_force;

        void attack(position pos, double speed_multiplier);
    public:
        snake(position pos, SDL_Texture* idle, SDL_Texture* jump, double view_range, double jump_force);
        void render(SDL_Renderer* renderer, double scale) override;
        void on_tile_collision(double speed_multiplier) override;
        void on_player_collision(entity& p, double speed_multiplier) override;
        void on_player_spot(entity& p, double speed_multiplier) override;
        bool does_collide(SDL_Rect collider, double scale);
        SDL_Rect get_collider(double scale) override;
        ~snake();
};