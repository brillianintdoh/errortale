#include "userNode.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/core/class_db.hpp>
using namespace godot;

void userNode::_bind_methods() {}

userNode::userNode() {
    speed = 100.0f;
    battle = 0;
}

userNode::~userNode() {}

void userNode::_ready() {
    user = Object::cast_to<AnimatedSprite2D>(get_node_internal("user"));
}

void userNode::_physics_process(double delta) {
    Input& i = *Input::get_singleton();
    Vector2 input_vec = Vector2();

    if(!isBattle) {
        camera->set_global_position(get_global_position());
        input_vec = Vector2(
            i.is_action_pressed("ui_right") - i.is_action_pressed("ui_left"),
            i.is_action_pressed("ui_down") - i.is_action_pressed("ui_up")
        );

        if(input_vec.x > 0) {
            user->play("work_right");
        }else if(input_vec.x < 0) {
            user->play("work_left");
        }else if(input_vec.y > 0) {
            user->play("work_down");
        }else if(input_vec.y < 0) {
            user->play("work_up");
        }else {
            user->stop();
            user->set_frame(0);
        }
    }else if(!battle) {
        user->play("work_right");
        user->stop();
        user->set_frame(0);
        battle = 1;
    }
    vec = input_vec * speed;
    set_velocity(vec);
    move_and_slide();
}