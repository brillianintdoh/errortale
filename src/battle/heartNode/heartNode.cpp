#include "heartNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
using namespace godot;

HeartNode::HeartNode() {}

HeartNode::~HeartNode() {}

void HeartNode::_bind_methods() {}

void HeartNode::_ready() {
}

void HeartNode::_physics_process(double delta) {
    if(isStart) {
        Input& i = *Input::get_singleton();
        Vector2 vec = Vector2(
            i.is_action_pressed("ui_right") - i.is_action_pressed("ui_left"),
            i.is_action_pressed("ui_down") - i.is_action_pressed("ui_up")
        );
        set_velocity(vec * 300.0f);
        move_and_slide();
    }
}