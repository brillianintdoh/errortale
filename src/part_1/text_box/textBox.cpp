#include "textBox.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/classes/file_access.hpp>
#include<godot_cpp/classes/scene_tree.hpp>
#define NI 2

void TextBox::_bind_methods() {}

TextBox::TextBox() {
    ni = 0;
    isNext = 1;
    length = 0.5;
    isNext = 1;
    isStart = 0;
}

TextBox::~TextBox() {}

void TextBox::_ready() {
    Ref<FileAccess> json_file = FileAccess::open("res://data/corridor/sans.json", FileAccess::READ);
    sans_data = json->parse_string(json_file->get_as_text());
    text = Object::cast_to<RichTextLabel>(get_node_internal("window/text"));
    startSound = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound"));
}

void TextBox::text_next() {
    text->set_text(sans_data.get(ni).get("text"));
    int type = sans_data.get(ni).get("type");
    text->set_visible_ratio(0);
    ni+=1;
    if(ni == NI+1) {
        startSound->play();
        get_tree()->change_scene_to_file("res://scene/battle/part_2.tscn");
    }
}

void TextBox::_process(double delta) {
    if(isSans && !isNext) {
        if(text->get_visible_ratio() >= 1) {
            Input& i = *Input::get_singleton();
            if(i.is_action_pressed("click")) {
                isNext = 1;
            }
        }else {
            text->set_visible_ratio(text->get_visible_ratio() + delta); 
        }
    }else if(isSans && isNext) {
        text_next();
        isNext = 0;
    }
}