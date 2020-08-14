#pragma once

#include <SDL2/SDL.h>

struct position {
    double x;
    double y;
};


class entity {
    protected:
        position pos;
        position velocity;
    public:
        entity(position pos);
        position get_position();
        virtual void add_force(position velocity);
        virtual void render(SDL_Renderer* renderer, double scale) = 0;
        virtual void update();
        virtual void on_tile_collision() = 0;
        virtual bool does_collide(SDL_Rect collider) = 0;
        virtual ~entity();
};

class enemy : public entity {
    public:
        enemy(position pos);
        virtual void on_player_collision(entity& player) = 0;
        virtual ~enemy();
};