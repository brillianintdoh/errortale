#include "textBox.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/classes/file_access.hpp>
#include<godot_cpp/classes/json.hpp>
#include<godot_cpp/classes/resource_loader.hpp>
using namespace godot;

TextBox::TextBox() {
    index = 0;
    times = 0;
    isFirst = true;
}

TextBox::~TextBox() {}

void TextBox::_bind_methods() {}

void TextBox::_ready() {
    Ref<FileAccess> file = FileAccess::open("res://data/textBox.json", FileAccess::READ);
    json = JSON::parse_string(file->get_as_text());
    head = Object::cast_to<TextureRect>(get_node_internal("window/head"));
    text = Object::cast_to<RichTextLabel>(get_node_internal("window/text"));
    error_start = Object::cast_to<AnimatedSprite2D>(get_node_internal("errorStart"));
    ResourceLoader* resource_loader = ResourceLoader::get_singleton();

    for(int i=1; i <= 2; i++) {
        Ref<Texture2D> resource = resource_loader->load("res://assets/sans/sans_head_"+String::num(i)+".png");
        heads.push_back(resource);
    }

    Array ar = json;
    lenght = ar.size();
}

void TextBox::_process(double delta) {
    if(isSans == 2) {
        Input& i = *Input::get_singleton();
        if(i.is_action_pressed("ui_select") || i.is_action_pressed("ui_accept") || i.is_key_pressed(KEY_Z)) {
            nextText();
        }

        if(isFirst) {
            nextText();
            isFirst = false;
        }

        float ratio = text->get_visible_ratio();
        if(1 >= ratio) {
            if(time <= times) {
                times = 0;
                text->set_visible_ratio(ratio+delta);

                if(lenght <= index) {
                    error_start->set_visible(true);
                    error_start->play();
                }
            }else {
                times+=delta;
            }
        }
    }
}

void TextBox::nextText() {
    if(lenght > index) {
        text->set_visible_ratio(0);
        text->set_text(json.get(index).get("text"));
        head->set_texture(heads[json.get(index).get("head")]);
        time = json.get(index).get("time");
        index++;
    }
}