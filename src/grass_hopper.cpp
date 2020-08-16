#include "grass_hopper.h"

grass_hopper::grass_hopper(position pos, SDL_Texture* tex, double jump_force) : enemy{pos, 0}, tex(tex), jump_force(jump_force) {

}

void grass_hopper::on_player_collision(entity& p, double speed_multiplier) {
    ((player&)p).heal(50);
}

void grass_hopper::on_player_spot(entity& p, double speed_multiplier) {
}

void grass_hopper::render(SDL_Renderer* renderer, double scale) {
    SDL_Rect target_pos = SDL_Rect{(int)this->pos.x, (int)(512 - this->pos.y), (int)(32 * scale), (int)(32 * scale)};
    SDL_RenderCopy(renderer, this->tex, nullptr, &target_pos);
}

SDL_Rect grass_hopper::get_collider(double scale) {
    return SDL_Rect{(int)this->pos.x, (int)(512 - this->pos.y), (int)(32 * scale), (int)(32 * scale)};
}

void grass_hopper::on_tile_collision(double speed_multiplier) {
    this->velocity.x = -0.25;
    this->velocity.y = this->jump_force * (speed_multiplier / 0.05);
  //  this->add_force(position{-0.25, this->jump_force});
}

grass_hopper::~grass_hopper ()
{
}
