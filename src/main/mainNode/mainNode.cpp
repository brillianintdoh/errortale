#include "mainNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/classes/scene_tree.hpp>
using namespace godot;

MainNode::MainNode() {
    start_time = 0;
    isON = 0;
}

MainNode::~MainNode() {}

void MainNode::_bind_methods() {}

void MainNode::init() {
    Object::cast_to<Sprite2D>(get_node_internal("last_corridor"))->set_visible(false);

    res.push_back(resource_loader->load("res://assets/logo_2.png")); // 0
    shader->set_visible(false);
    gameTitle->set_visible(false);
    title->set_visible(false);
    camera->set_global_position(gameTitle->get_global_position());
}

void MainNode::_ready() {
    resource_loader = ResourceLoader::get_singleton();
    camera = Object::cast_to<Camera2D>(get_node_internal("camera"));
    title = Object::cast_to<Sprite2D>(get_node_internal("title"));
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    sans = Object::cast_to<Sprite2D>(get_node_internal("sans/sprite"));
    logoPlay = Object::cast_to<AudioStreamPlayer>(get_node_internal("logoPlay"));
    shader = Object::cast_to<TextureRect>(get_node_internal("shader"));
    resource_loader = ResourceLoader::get_singleton();
    gameTitle = Object::cast_to<Sprite2D>(get_node_internal("gameTitle"));
    btn1 = Object::cast_to<Label>(get_node_internal("gameTitle/btn1"));
    btn2 = Object::cast_to<Label>(get_node_internal("gameTitle/btn2"));
    window = get_window();

    init();
}

void MainNode::_process(double delta) {
    if(isGameStart) {
        get_tree()->change_scene_to_file("res://scene/sans.tscn");
    }

    if(!isStart) {
        on(delta);
    }else if(isSans) {
        background->set_z_index(2);
        if(isSans == 2) {
            Node2D* node = Object::cast_to<Node2D>(get_node_internal("sans"));
            node->set_visible(true);
            Vector2 user_pos = camera->get_global_position();
            node->set_global_position(user_pos);
            sans->set_global_position(user_pos + Vector2(window->get_size().width/3, 0));
        }
    }
}

void MainNode::on(double delta) {
    if(isON == 4) {
        Input& i = *Input::get_singleton();
        Color colorON = Color("#ffff00");
        Color colorOff = Color("#ffffff");
        if(i.is_action_pressed("ui_left")) {
            if(btn2->get_theme_color("font_color") == colorON) {
                btn1->add_theme_color_override("font_color", colorON);
                btn2->add_theme_color_override("font_color", colorOff);
            }
        }else if(i.is_action_pressed("ui_right")) {
            if(btn1->get_theme_color("font_color") == colorON) {
                btn1->add_theme_color_override("font_color", colorOff);
                btn2->add_theme_color_override("font_color", colorON);
            }
        }else if(i.is_action_pressed("select")) {
            if(btn1->get_theme_color("font_color") == colorON) {
                gameTitle->set_visible(false);
                Object::cast_to<Sprite2D>(get_node_internal("last_corridor"))->set_visible(true);
                isStart = true;
            }else if(btn2->get_theme_color("font_color") == colorON) {
            }
        }
    }else if(isON == 3) {
        if(start_time >= 2.5) {
            gameTitle->set_visible(true);
            title->set_visible(false);
            isON = 4;
            start_time = 0;
        }else start_time+=delta;
    }else if(isON == 2) {
        if(start_time >= 7) {
            title->set_texture(res[0]);
            Vector2 pos = title->get_position();
            pos.y += 50;
            title->set_position(pos);
            logoPlay->play();

            shader->set_visible(false);
            isON = 3;
            start_time = 0;
        }else start_time+=delta;
    }else if(isON == 1) {
        if(start_time >= 3.5) {
            shader->set_visible(true);
            isON = 2;
            start_time = 0;
        }else start_time+=delta;
    }else if(isON == 0) {
        if(start_time >= 1.5) {
            start_time = 0;
            logoPlay->play();
            title->set_visible(true);
            isON = 1;
        }else start_time += delta;
    }
}