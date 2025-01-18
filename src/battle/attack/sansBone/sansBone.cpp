#include "sansBone.h"
using namespace godot;

SansBone::SansBone() {}

SansBone::~SansBone() {}

void SansBone::_bind_methods() {}

void SansBone::_ready() {
    is = false;
    isON = true;
}

void SansBone::_process(double delta) {
    if(is) {
        Vector2 new_vec = get_position().lerp(target, delta*speed);
        set_position(new_vec);

        if(new_vec.distance_to(target) < 3.0f && isON) queue_free();
    }
}

void SansBone::set_target(Vector2 vec, double speed, int on) {
    target = vec;
    this->speed = speed;
    is = true;
    isON = on;
}