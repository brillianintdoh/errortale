#include "part2.h"
#include<godot_cpp/classes/file_access.hpp>
#include<godot_cpp/core/class_db.hpp>
using namespace godot;

void Part2::_bind_methods() {}

Part2::Part2() {
    wait[0] = 0.1;
    wait[1] = 0.3;
    wait[2] = 0.5;
    wait[3] = 0.7;
    sleep_s = 0;
    sleep_b = 0;
    isShake = 1;
    json_index = 0;
}

Part2::~Part2() {}

void Part2::shake(double delta) {
    camera->set_drag_horizontal_offset(0);
    camera->set_drag_vertical_offset(0);
    sleep_s+=delta;
    if(sleep_s <= wait[0]) {
        camera->set_drag_horizontal_offset(0.5);
        camera->set_drag_vertical_offset(0.5);
    }else if(sleep_s <= wait[1]) {
        camera->set_drag_horizontal_offset(-0.5);
        camera->set_drag_vertical_offset(-0.5);
    }else if(sleep_s <= wait[2]) {
        camera->set_drag_horizontal_offset(0.5);
        camera->set_drag_vertical_offset(-0.5);
    }else if(sleep_s <= wait[3]) {
        camera->set_drag_horizontal_offset(-0.5);
        camera->set_drag_vertical_offset(0.5);
        sleep_s = 0;
    }
}

void Part2::black_scene(double delta) {
    sleep_b+=delta;

    if(wait[1] >= sleep_s) {
        background->set_z_index(5);
        sleep_b = 0;
    }else {
        background->set_z_index(-1);
    }
}

void Part2::_ready() {
    user = Object::cast_to<CharacterBody2D>(get_node_internal("Heart"));
    camera = Object::cast_to<Camera2D>(get_node_internal("Camera"));
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    sound = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound"));
    Ref<FileAccess> file = FileAccess::open("res://data/battle/battle.json", FileAccess::READ);
    data_json = json->parse_string(file->get_as_text());

    Callable fun = callable_mp(this, &Part2::sound_end);
    sound->connect("finished", fun);
    sound->play();
}

void Part2::sound_end() {
    sound->get_stream()->set_path(data_json.get(json_index).get("sound"));
    sound->play();
    json_index+=1;
    isShake = 0;
}

void Part2::_process(double delta) {
    if(isShake) {
        shake(delta);
        black_scene(delta);
    }
}