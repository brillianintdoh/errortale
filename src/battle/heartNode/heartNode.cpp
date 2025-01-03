#include "heartNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/classes/resource_loader.hpp>
using namespace godot;

HeartNode::HeartNode() {
    isBlue = false;
    isUP = true;
    times = 0;
}

HeartNode::~HeartNode() {}

void HeartNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("onCollision", "node"), &HeartNode::onCollision);
}

void HeartNode::_ready() {
    sprite = Object::cast_to<Sprite2D>(get_node_internal("sprite"));
    hpBar = Object::cast_to<TextureProgressBar>(get_node_internal("../ui/hpBar"));

    ResourceLoader* loader = ResourceLoader::get_singleton();
    hearts["red"] = loader->load("res://assets/user/battle/red.png");
    hearts["blue"] = loader->load("res://assets/user/battle/blue.png");
    gravity = Vector2(0,0);
}

void HeartNode::_physics_process(double delta) {
    if(!isStart) return;
    Input& i = *Input::get_singleton();
    Vector2 vec = Vector2(
        i.is_action_pressed("ui_right") - i.is_action_pressed("ui_left"),
        i.is_action_pressed("ui_down") - i.is_action_pressed("ui_up")
    );
    Vector2 curr = get_linear_velocity();

    if(isBlue) {
        curr += gravity * delta;
        if(isUP) curr.y += vec.y * 80.0f;
        curr.x += vec.x * 35.0f;
    }else curr = vec * 400.0f;

    if(isUP && i.is_action_pressed("ui_up")) {
        if(0.3 <= times) {
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
    }
}

void HeartNode::set_blue(int is, int x, int y) {
    sprite->set_texture(is ? hearts["blue"] : hearts["red"]);
    isBlue = is;
    if(is) gravity = Vector2(x, y) * 100.0f;
    else gravity = Vector2(0, 0);
}