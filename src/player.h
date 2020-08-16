#pragma once

#include "animatable.h"
#include "entity_types.h"

class player : public animatable, public entity
{
private:
    double blood_level;
    double max_blood;
public:
    player(position start_position, SDL_Texture* texture_map, double max_blood, size_t timer = 0);
    void render(SDL_Renderer* renderer, double scale) override;
    void on_tile_collision(double speed_multiplier) override;
    void update() override;
    void add_force(position velocity) override;
    double get_blood();
    double get_max_blood();
    void set_max_blood(double amount);
    void set_blood_level(double amount);
    void damage(double amount);
    void heal(double amount);
    void die();
    bool is_dead();
    SDL_Rect get_collider(double scale) override;
    ~player();
};