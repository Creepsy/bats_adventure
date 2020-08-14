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

        void attack(position pos);
    public:
        snake(position pos, SDL_Texture* idle, SDL_Texture* jump, double view_range, double jump_force);
        void render(SDL_Renderer* renderer, double scale) override;
        void on_tile_collision() override;
        void on_player_collision(entity& p) override;
        void on_player_spot(entity& p) override;
        bool does_collide(SDL_Rect collider) override;
        ~snake();
};