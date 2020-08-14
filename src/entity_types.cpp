#include "entity_types.h"

entity::entity(position pos) : pos(pos), velocity{0, 0} {

}

position entity::get_position() {
    return this->pos;
}

void entity::set_position(position pos) {
    this->pos = pos;
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

enemy::enemy(position pos, double view_range) : entity{pos}, view_range(view_range) {

}

bool enemy::can_see(position pos) {
    double dist_x = fabs(this->pos.x - pos.x), dist_y = fabs(this->pos.y - pos.y);
    return sqrt(dist_x * dist_x + dist_y * dist_y) <= this->view_range;
}

enemy::~enemy() {
}