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
        void set_position(position pos);
        virtual void add_force(position velocity);
        virtual void render(SDL_Renderer* renderer, double scale) = 0;
        virtual void update();
        virtual void on_tile_collision(double speed_multiplier) = 0;
        virtual bool does_collide(SDL_Rect collider, double scale);
        virtual SDL_Rect get_collider(double scale) = 0;
        virtual ~entity();
};

class enemy : public entity {
    protected:
        double view_range;
    public:
        enemy(position pos, double view_range);
        virtual void on_player_collision(entity& p, double speed_multiplier) = 0;
        virtual void on_player_spot(entity& p, double speed_multiplier) = 0;
        bool can_see(position pos);
        virtual ~enemy();
};