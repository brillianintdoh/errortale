#include "heartNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/classes/resource_loader.hpp>
using namespace godot;

HeartNode::HeartNode() {
    isBlue = false;
    isUP = true;
    times = 0;
    ui_direction = "ui_up";
}

HeartNode::~HeartNode() {}

void HeartNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("onCollision", "node"), &HeartNode::onCollision);
}

void HeartNode::_ready() {
    sprite = Object::cast_to<Sprite2D>(get_node_internal("sprite"));
    bell = Object::cast_to<AudioStreamPlayer>(get_node_internal("bell"));

    ResourceLoader* loader = ResourceLoader::get_singleton();
    hearts["red"] = loader->load("res://assets/user/battle/red.png");
    hearts["blue"] = loader->load("res://assets/user/battle/blue.png");
    gravity = Vector2(0,0);
}

void HeartNode::_physics_process(double delta) {
    if(!isStart || isMyTurn) return;
    Input& i = *Input::get_singleton();
    Vector2 vec = Vector2(
        i.is_action_pressed("ui_right") - i.is_action_pressed("ui_left"),
        i.is_action_pressed("ui_down") - i.is_action_pressed("ui_up")
    );
    Vector2 curr = get_linear_velocity();

    if(isBlue) {
        curr += gravity * delta;
        if(ui_direction == "ui_down" || ui_direction == "ui_up") {
            if(isUP) curr.y += vec.y * 80.0f;
            curr.x += vec.x * 35.0f;
        }else if(ui_direction == "ui_left" || ui_direction == "ui_right") {
            if(isUP) curr.x += vec.x * 35.0f;
            curr.y += vec.y * 80.0f;
        }
    }else curr = vec * 400.0f;

    if(isUP && i.is_action_pressed(ui_direction)) {
        if(cool <= times) {
            times = 0;
            isUP = false;
        }else times += delta;
    }

    set_linear_velocity(curr);
}

void HeartNode::onCollision(Node* node) {
    String name = node->get_name().to_utf8_buffer().get_string_from_utf8();
    if(name == "frame_body") {
        isUP = true;
        if(isBlue == 1) {
            impact->play();
            isBlue = 2;
        }
    }
}

void HeartNode::set_blue(int is, int x, int y) {
    sprite->set_texture(is ? hearts["blue"] : hearts["red"]);
    if(isBlue != is) bell->play();
    isBlue = is;
    if(is) {
        gravity = Vector2(x, y) * 100.0f;
        double angle = atan2(y, x);
        sprite->set_rotation(angle - Math_PI / 2);

        if(angle >= -Math_PI/4 && angle < Math_PI/4)
            ui_direction = "ui_left";
        else if(angle >= Math_PI/4 && angle < 3*Math_PI/4)
            ui_direction = "ui_up";
        else if(angle >= -3*Math_PI/4 && angle < -Math_PI/4)
            ui_direction = "ui_down";
        else
            ui_direction = "ui_right";
    }else {
        gravity = Vector2(0, 0);
        sprite->set_rotation(0);
    }
}

void HeartNode::set_coolTime(double time) {
    cool = time;
}