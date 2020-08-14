#include "player.h"

player::player(position start_position, SDL_Texture* texture_map, double max_blood, size_t timer) : 
    entity{start_position}, animatable{texture_map, 8, 32, 32, 32, timer}, max_blood(max_blood), blood_level(max_blood / 2) {
}

void player::render(SDL_Renderer* renderer, double scale) {
    SDL_Rect screen_pos = SDL_Rect{(int)(this->pos.x - this -> width * scale / 2),
                                   (int)((512 - this->pos.y) - this -> height * scale / 2),
                                   (int)(this->width * scale),
                                   (int)(this->height * scale)};
    this->animatable::render(screen_pos, renderer, -this->velocity.y * 10);
}

void player::on_tile_collision() {
    this->die();
}

bool player::does_collide(SDL_Rect collider) {
    int real_y = 512 - this->pos.y; 
    return this->pos.x + this->width / 4 < collider.x + collider.w && this->pos.x + this->width / 4 * 3 > collider.x && real_y + this->height / 4 < collider.y + collider.h && real_y + this->height / 4 * 3 > collider.y;
}

void player::damage(double amount) {
    this->blood_level -= amount;
    if(blood_level < 0) this->die();
}

void player::die() {
    this->blood_level = 0;
    this->velocity.y = 0;
    this->velocity.x = 0;
}

bool player::is_dead() {
    return this->blood_level <= 0;
}

void player::update() {
    entity::update();
    animatable::update();

    if(this->pos.y < 0) {
        this->pos.y = 0;
        this->velocity.y = 0;
    } 

    if(this->pos.y > 512) {
        this->pos.y = 512;
        this->velocity.y = 0;
    }
}

void player::add_force(position velocity) {
    this->velocity.y += velocity.y;
    if(this->velocity.y > 6) this->velocity.y = 6;
}

double player::get_blood() {
    return this->blood_level;
}

double player::get_max_blood() {
    return this->max_blood;
}

player::~player() {

}