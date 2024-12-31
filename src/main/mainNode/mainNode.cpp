#include "mainNode.h"
#include<godot_cpp/classes/input.hpp>
#include<godot_cpp/classes/scene_tree.hpp>
#include "../../env/env.h"
using namespace godot;

MainNode::MainNode() {
    btn_lengtn = 2;
    start_time = 0;
    btnI = 0;
    isON = false;
}

MainNode::~MainNode() {}

void MainNode::_bind_methods() {}

void MainNode::init() {
    Object::cast_to<Node2D>(get_node_internal("gameTitle"))->set_visible(true);
    Object::cast_to<Sprite2D>(get_node_internal("last_corridor"))->set_visible(false);

    for(int i=1; i <= btn_lengtn; i++) {
        Ref<Texture2D> texture = resource_loader->load("res://assets/button/btn_"+String::num(i)+".png");
        Ref<Texture2D> texture_on = resource_loader->load("res://assets/button/btnOn_"+String::num(i)+".png");
        Sprite2D* btn = Object::cast_to<Sprite2D>(get_node_internal("gameTitle/ui/btn_"+String::num(i)));
        Vector2 vec = btn->get_position();
        vec.x -= 200+(i*130);
        btn->set_position(vec);
        btns.push_back(btn);
        res.push_back(texture);
        resOn.push_back(texture_on);
    }

    btns[0]->set_texture(res[0]);
    ui->set_position(Vector2(-200, -50));
    title->set_position(Vector2(135, -500));
    camera->set_global_position(Vector2(0,0));
    effect->set_visible(false);
}

void MainNode::_ready() {
    resource_loader = ResourceLoader::get_singleton();
    camera = Object::cast_to<Camera2D>(get_node_internal("camera"));
    ui = Object::cast_to<Control>(get_node_internal("gameTitle/ui"));
    title = Object::cast_to<Sprite2D>(get_node_internal("gameTitle/title"));
    effect = Object::cast_to<AnimatedSprite2D>(get_node_internal("gameTitle/errorEffect"));
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    sans = Object::cast_to<Sprite2D>(get_node_internal("sans/sprite"));
    resource_loader = ResourceLoader::get_singleton();
    window = get_window();

    init();
}

void MainNode::_process(double delta) {
    if(isGameStart) {
    }

    if(!isStart) {
        for(int i=0; i < btn_lengtn; i++) {
            Vector2 vec = btns[i]->get_position();
            if(vec.x < -200) {
                vec.x += 1.5;
                btns[i]->set_position(vec);
            }
        }

        Vector2 vec_ui = ui->get_position();
        if(vec_ui.x < -100) {
            vec_ui.x += 2;
            ui->set_position(vec_ui);
        }


        if(isON) {
            // on(delta);
        }else {
            if(start_time >= 5) {
                Vector2 vec_title = title->get_position();
                if(vec_title.y < -180) {
                    vec_title.y += 10;
                    title->set_position(vec_title);
                }else {
                    effect->set_visible(true);
                    effect->play();
                    isON = true;
                    start_time = 0;
                    btns[0]->set_texture(resOn[0]);
                }
            }else {
                start_time += delta;
            }
        }
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
    Input& i = *Input::get_singleton();
    if(i.is_action_pressed("ui_up")) {
        btns[btnI]->set_texture(res[btnI]);
        if(btnI == 0)
            btnI = btn_lengtn-1;
        else 
            btnI--;
        btns[btnI]->set_texture(resOn[btnI]);
    }else if(i.is_action_pressed("ui_down")) {
        btns[btnI]->set_texture(res[btnI]);
        if(btnI == btn_lengtn-1)
            btnI = 0;
        else
            btnI++;
        btns[btnI]->set_texture(resOn[btnI]);
    }else if(i.is_action_pressed("ui_select") || i.is_action_pressed("ui_accept")) {
        for(int i=0; i < btn_lengtn; i++) {
            if(btns[i]->get_texture() == resOn[i]) {
                if(i == 0) {
                    Object::cast_to<Node2D>(get_node_internal("gameTitle"))->set_visible(false);
                    Object::cast_to<Sprite2D>(get_node_internal("last_corridor"))->set_visible(true);
                    isStart = true;
                }else if(i == 1) {
                    get_tree()->quit();
                }
            }
        }
    }

    if(start_time >= 0.3) {
        effect->set_visible(false);
        if(start_time >= 1) {
            effect->set_visible(true);
            effect->play();
            start_time = 0;
        }
    }
    start_time += delta;
}