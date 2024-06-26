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
    isBlack = 0;
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

    if(wait[2] >= sleep_b) {
        background->set_z_index(5);
        sleep_b = 0;
    }else {
        background->set_z_index(-1);
    }
}

void Part2::_ready() {
    user = Object::cast_to<CharacterBody2D>(get_node_internal("Heart"));
    sans = Object::cast_to<AnimatedSprite2D>(get_node_internal("sans"));
    camera = Object::cast_to<Camera2D>(get_node_internal("Camera"));
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    sound = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound"));
    ui = Object::cast_to<Node2D>(get_node_internal("UI"));
    tools_menu = Object::cast_to<Control>(get_node_internal("UI/menu/tools"));
    tools[0] = Object::cast_to<RichTextLabel>(get_node_internal("UI/menu/tools/tools_1"));
    Ref<FileAccess> data_file = FileAccess::open("res://data/battle/battle.json", FileAccess::READ);
    Ref<FileAccess> tools_file = FileAccess::open("res://data/battle/tool.json", FileAccess::READ);
    data_json = json->parse_string(data_file->get_as_text());
    tools_json = json->parse_string(tools_file->get_as_text());

    Callable fun_sound = callable_mp(this, &Part2::sound_end);
    Callable fun_sans = callable_mp(this, &Part2::sansAnim_end);
    sound->connect("finished", fun_sound);
    sans->connect("animation_finished", fun_sans);
    sound->play();


    // 아이템 메뉴에 추가
    int x = 45,y = 25, p = 1;
    tools[0]->set_position(Vector2(x,y));
    tools[0]->set_text(tools_json.get(0).get("item"));
    for(int i=1; i < 8; i++) {
        if(p) { 
            y+=75;
        }else {
            y-=75;
            x+=200;
        }
        tools[i] = (RichTextLabel*) tools[0]->duplicate();
        tools[i]->set_position(Vector2(x,y));
        tools[i]->set_text(tools_json.get(i).get("item"));
        tools_menu->add_child(tools[i]);
        p = (p == 1) ? 0 : 1;
    }
}

void Part2::sound_end() {
    sound->get_stream()->set_path(data_json.get(json_index).get("sound"));
    json_index+=1;
    isShake = 0;
    isBlack = 1;
    camera->set_drag_horizontal_offset(0);
    camera->set_drag_vertical_offset(0);
    sans->play("sans_start");
    sound->play();
}

void Part2::sansAnim_end() {
    printf("wow");
}

void Part2::_process(double delta) {
    if(isShake) {
        shake(delta);
    }

    if(isBlack) {
        black_scene(delta);
    }
}