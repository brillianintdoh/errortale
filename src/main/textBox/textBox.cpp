#include "textBox.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
using namespace godot;

TextBox::TextBox() {}

TextBox::~TextBox() {}

void TextBox::_bind_methods() {}

void TextBox::_ready() {
    head = Object::cast_to<TextureRect>(get_node_internal("window/head"));
    text = Object::cast_to<RichTextLabel>(get_node_internal("window/text"));
}

void TextBox::_process(double delta) {
    if(isBattle) {
        Input& i = *Input::get_singleton();
        if(i.is_action_pressed("ui_select") || i.is_action_pressed("ui_accept") || i.is_key_pressed(KEY_Z)) {
        }
    }
}