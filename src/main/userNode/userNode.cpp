#include "userNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
using namespace godot;

UserNode::UserNode() {
    isMove = true;
    start_time = 0;
}

UserNode::~UserNode() {}

void UserNode::_bind_methods() {}

void UserNode::_ready() {
    animated = Object::cast_to<AnimatedSprite2D>(get_node_internal("Animated"));
    set_scale(Vector2(0.6, 0.664));
    set_visible(false);
}

void UserNode::_physics_process(double delta) {
    if(!isStart) return;

    Vector2 pos = get_position();
    if(pos.x > 500 || isSans) {
        if(start_time > 5) {
            isMove = false;
            animated->play("right");
            animated->stop();
            animated->set_frame(0);
            set_global_position(camera->get_global_position() - Vector2(window->get_size().width/3, 20));
            isSans = 2;
        }else {
            isSans = true;
            set_z_index(3);
            set_scale(Vector2(0.479145, 0.530042));
            start_time+=delta;
        }
    }

    if(isMove) {
        Input& i = *Input::get_singleton();
        Vector2 vec = Vector2(
            i.is_action_pressed("ui_right") - i.is_action_pressed("ui_left"),
            i.is_action_pressed("ui_down") - i.is_action_pressed("ui_up")
        );
        Vector2 c_pos = get_global_position();
        if(!isSans) c_pos.y -= 150;
        camera->set_global_position(c_pos);
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
        set_velocity(vec * 200.0f);
        move_and_slide();
    }
}