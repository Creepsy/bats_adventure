#include "snake.h"

snake::snake(position pos, SDL_Texture* idle, SDL_Texture* jump, double view_range, double jump_force) :
    enemy{pos, view_range}, idle(idle), jump(jump), attacking(false), jump_force(jump_force), damaged(false) {
}

void snake::render(SDL_Renderer* renderer, double scale) {
    if(this->attacking) {
        SDL_Rect target_pos = SDL_Rect{(int)this->pos.x, (int)(512 - this->pos.y), (int)(51 * scale), (int)(8 * scale)};
        SDL_RenderCopyEx(renderer, this->jump, nullptr, &target_pos, this->velocity.y * 10, nullptr, SDL_FLIP_NONE);
    } else {
        SDL_Rect target_pos = SDL_Rect{(int)this->pos.x, (int)(512 - this->pos.y), (int)(32 * scale), (int)(32 * scale)};
        SDL_RenderCopy(renderer, this->idle, nullptr, &target_pos);
    }
}

void snake::on_tile_collision() {
    if(!this->attacking) {
        this->velocity.x = 0;
        this->velocity.y = 0;
    }
}

void snake::on_player_collision(entity& p) {
    if(!this->damaged) {
        ((player&)p).damage(25);
        this->damaged = true;
    }
}

void snake::on_player_spot(entity& p) {
    if(!this->attacking) {
        this->attack(p.get_position());
    }
}

void snake::attack(position pos) {
    this->attacking = true;
    position direction{this->pos.x - pos.x, this->pos.y - pos.y};
    double distance = sqrt(fabs(direction.x) * fabs(direction.x) + fabs(direction.y) * fabs(direction.y));
    direction.x /= distance;
    direction.y /= distance;

    this->add_force(position{-direction.x * this->jump_force, -direction.y * this->jump_force * 2});
}

SDL_Rect snake::get_collider(double scale) {
    if(this->attacking) {
        return SDL_Rect{(int)this->pos.x, (int)(512 - this->pos.y), (int)(51 * scale), (int)(8 * scale)};
    } else {
        return SDL_Rect{(int)(this->pos.x + 32 * scale / 4), (int)(512 - this->pos.y + 32 * scale / 2), (int)(32 * scale / 3 * 2), (int)(32 * scale / 2)};
    }
}

snake::~snake() {
}