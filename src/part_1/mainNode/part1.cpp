#include "part1.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/classes/window.hpp>
using namespace godot;

void Part1::_bind_methods() {}

Part1::Part1() {
    slep = 0;
    wait = 0.5f;
    wait_i = 6;
    start = 1;
    wait_stop = 0;
}

Part1::~Part1() {}

void Part1::_ready() {
    user = Object::cast_to<CharacterBody2D>(get_node_internal("last_corridor/userNode"));
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    camera = Object::cast_to<Camera2D>(get_node_internal("Camera"));
    sans = Object::cast_to<Sprite2D>(get_node_internal("last_corridor/sans"));
    text_box = Object::cast_to<Control>(get_node_internal("last_corridor/TextBox"));
}

void Part1::battle_start() {
    wait_stop = wait_i+2;
    background->set_z_index(5);
    user->set_z_index(6);
    sans->set_z_index(6);
    text_box->set_z_index(6);
    Vector2 user_pos = user->get_global_position();
    text_box->set_global_position(user_pos);
    text_box->set_visible(true);
    Vector2 pos = user_pos - Vector2(get_window()->get_size().width/3, 0);
    user->set_global_position(pos);
    pos = user_pos + Vector2(get_window()->get_size().width/3, 0);
    sans->set_global_position(pos);
    sans->set_visible(true);
    isSans = 1;
}

void Part1::_process(double delta) {
    if(user->get_global_position().x >= 1100) {
        if(!wait_stop) {
            isBattle = 1;
        }

        if(wait_stop < wait_i) {
            shake(delta);
        }else if(wait_stop == wait_i) {
            if(start) {
                battle_start();
                start = 0;
                slep = 0;
            }
        }
    }

    if(isBattle_start) {
        shake(delta);
    }
}

void Part1::shake(double delta) {
    slep+=delta;

    if(slep >= wait) {
        background->set_z_index(-1);
        slep = 0;
        wait_stop++;
    }else {
        background->set_z_index(10);
    }
}