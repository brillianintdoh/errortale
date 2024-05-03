#include "heart.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/classes/input.hpp>
using namespace godot;

void Heart::_bind_methods() {}

Heart::Heart() {
    speed = 200.0f;
}

Heart::~Heart() {}

void Heart::_physics_process(double delta) {
    Input& i = *Input::get_singleton();

    Vector2 input_vec = Vector2(
        i.is_action_pressed("ui_right") - i.is_action_pressed("ui_left"),
        i.is_action_pressed("ui_down") - i.is_action_pressed("ui_up")
    );
    vec = input_vec * speed;

    set_velocity(vec);
    move_and_slide();
}