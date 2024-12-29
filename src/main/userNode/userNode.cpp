#include "userNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
using namespace godot;

UserNode::UserNode() {
    isMove = true;
}

UserNode::~UserNode() {}

void UserNode::_bind_methods() {}

void UserNode::_ready() {
    animated = Object::cast_to<AnimatedSprite2D>(get_node_internal("Animated"));
    set_visible(false);
}

void UserNode::_physics_process(double delta) {
    if(isStart) {
        Vector2 pos = get_position();
        if(pos.x < 1000 && isMove) {
            Input& i = *Input::get_singleton();
            Vector2 vec = Vector2(
                i.is_action_pressed("ui_right") - i.is_action_pressed("ui_left"),
                i.is_action_pressed("ui_down") - i.is_action_pressed("ui_up")
            );
            camera->set_global_position(get_global_position());
            set_visible(true);

            if(vec.x > 0) {
                animated->play("right");
            }else if(vec.x < 0) {
                animated->play("left");
            }else if(vec.y > 0) {
                animated->play("down");
            }else if(vec.y < 0) {
                animated->play("up");
            }else {
                animated->stop();
                animated->set_frame(0);
            }

            set_velocity(vec * 150.0f);
            move_and_slide();
        }else {
            isMove = false;
            animated->play("right");
            animated->stop();
            animated->set_frame(0);
            set_global_position(camera->get_global_position() - Vector2(window->get_size().width/3, 20));
            set_z_index(3);
            isBattle = true;
        }
    }
}