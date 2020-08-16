#include "snake.h"

#include "math.h"

snake::snake(position pos, SDL_Texture* idle, SDL_Texture* jump, double view_range, double jump_force) :
    enemy{pos, view_range}, idle(idle), jump(jump), attacking(false), jump_force(jump_force), damaged(false) {
}

void snake::render(SDL_Renderer* renderer, double scale) {
    if(this->attacking) {
        double rotation = atan(this->velocity.y / this->velocity.x) * (double)180 / M_PI;
        SDL_Rect target_pos = SDL_Rect{(int)this->pos.x, (int)(512 - this->pos.y), (int)(51 * scale), (int)(8 * scale)};
        SDL_RenderCopyEx(renderer, this->jump, nullptr, &target_pos, -rotation, nullptr, SDL_FLIP_NONE);
    } else {
        SDL_Rect target_pos = SDL_Rect{(int)this->pos.x, (int)(512 - this->pos.y), (int)(32 * scale), (int)(32 * scale)};
        SDL_RenderCopy(renderer, this->idle, nullptr, &target_pos);
    }
}

bool snake::does_collide(SDL_Rect collider, double scale) {
    if(this->attacking) {
        position center = position{this->pos.x + 51 * scale / 2, 512 - this->pos.y + 8 * scale / 2};
        double dist = sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
        double n_x = this->velocity.x / dist, n_y = this->velocity.y / dist;

        for(int i = -3; i <= 3; i++) {
            SDL_Rect col = SDL_Rect{(int)(center.x + -n_x * i * 10 - 8), (int)(center.y + n_y * i * 10 - 8), 16, 16};
            if(col.x < collider.x + collider.w && col.x + col.w > collider.x && col.y < collider.y + collider.h && col.y + col.h  > collider.y) return true;
        }
        return false;
    }

    return entity::does_collide(collider, scale);
}

void snake::on_tile_collision(double speed_multiplier) {
    if(!this->attacking) {
        this->velocity.x = 0;
        this->velocity.y = 0;
    }
}

void snake::on_player_collision(entity& p, double speed_multiplier) {
    if(!this->damaged) {
        ((player&)p).damage(25);
        this->damaged = true;
    }
}

void snake::on_player_spot(entity& p, double speed_multiplier) {
    if(!this->attacking) {
        this->attack(p.get_position(), speed_multiplier);
    }
}

void snake::attack(position pos, double speed_multiplier) {
    if(pos.x < this->pos.x) {
        this->attacking = true;
        position direction{this->pos.x - pos.x, this->pos.y - pos.y};
        double distance = sqrt(fabs(direction.x) * fabs(direction.x) + fabs(direction.y) * fabs(direction.y));
        direction.x /= distance;
        direction.y /= distance;

        this->add_force(position{-direction.x * this->jump_force * (speed_multiplier / 0.05), -direction.y * this->jump_force * 2 * (speed_multiplier / 0.05)});
    }
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