#include "entity_types.h"

entity::entity(position pos) : pos(pos), velocity{0, 0} {

}

position entity::get_position() {
    return this->pos;
}

void entity::add_force(position velocity) {
    this->velocity.x += velocity.x;
    this->velocity.y += velocity.y;
}

void entity::update() {
    this->pos.x += this->velocity.x;
    this->pos.y += this->velocity.y;
}

entity::~entity() {
}

enemy::enemy(position pos) : entity{pos} {

}

enemy::~enemy() {
}