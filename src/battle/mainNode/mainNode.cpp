#include "mainNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/resource_loader.hpp>
using namespace godot;

BattleNode::BattleNode() {
    times = 0;
    is = 0;
    cool = 0;

    shakeCool = 0;
    backCool = 0;
    backIs = false;
    is_shaking = false;
}

BattleNode::~BattleNode() {}

void BattleNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("music_start_end"), &BattleNode::music_start_end);
    ClassDB::bind_method(D_METHOD("animated_start_end"), &BattleNode::animated_start_end);
}

void BattleNode::_ready() {
    camera = Object::cast_to<Camera2D>(get_node_internal("camera"));
    sans = Object::cast_to<AnimatedSprite2D>(get_node_internal("sans"));
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    heart = Object::cast_to<HeartNode>(get_node_internal("HeartNode"));
    window = get_window();

    ResourceLoader* loader = ResourceLoader::get_singleton();

    audio["noise"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/start_noise"));
    audio["start"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/battleStart"));
    music["start"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/start"));
    music["sans"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/sans"));

    isStart = false;
    isGameStart = false;
    background->set_z_index(3);
    heart->set_z_index(4);
    heart->set_global_position(camera->get_global_position() - Vector2(window->get_size().width/3, 20));
    sans->play("page_1");
    sans->stop();
    sans->set_frame(0);
}

void BattleNode::init() {
    sans->set_speed_scale(2.5);
    background->set_z_index(-1);
    heart->set_z_index(0);
    heart->set_linear_velocity(Vector2(0,0));
}

void BattleNode::_process(double delta) {
    if(isStart == 1) {
        background->set_z_index(-1);
        heart->set_z_index(0);
        sans->play("page_1");
        isStart = 2;
    }else if(!isStart) {
        start(delta); 
    }

    if(times >= 6.2 && is == 1) {
        is = 2;
        sans->set_speed_scale(1);
        sans->play("battle_start");
    }else {
        times+=delta;
    }

    effects(delta);
}

void BattleNode::start(double delta) {
    if(cool <= 1) {
        cool+=delta;
        if(times >= 0.2) {
            times = 0;
            background->set_z_index(3);
            Object::cast_to<AudioStreamPlayer>(audio["noise"])->play();
        }else {
            times += delta;
            background->set_z_index(5);
        }
    }else {
        if(!is) {
            Object::cast_to<AudioStreamPlayer>(audio["start"])->play();
            is = true;
        }

        Vector2 vec = heart->get_global_position();
        if(vec.x < -0.4 && vec.y < -0.4) {
            background->set_z_index(3);
            Vector2 new_pos = vec.lerp(Vector2(0,0), delta * 2);
            heart->set_global_position(new_pos);
            times = 0;
        }else {
            if(times >= 1) {
                shake_camera(6, 0.5, 0.5);
                times = 0;
                cool = 0;
                isStart = true;
                Object::cast_to<AudioStreamPlayer>(music["start"])->play();
            }else {
                times+=delta;
                background->set_z_index(5);
            }
        }
    }
}