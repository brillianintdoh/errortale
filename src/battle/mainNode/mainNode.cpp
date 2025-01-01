#include "mainNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/audio_stream_player.hpp>
using namespace godot;

BattleNode::BattleNode() {
    times = 0;
    is = 0;
    cool = 0;
}

BattleNode::~BattleNode() {}

void BattleNode::_bind_methods() {}

void BattleNode::_ready() {
    camera = Object::cast_to<Camera2D>(get_node_internal("camera"));
    sans = Object::cast_to<AnimatedSprite2D>(get_node_internal("sans"));
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    heart = Object::cast_to<HeartNode>(get_node_internal("HeartNode"));
    window = get_window();

    init();
}

void BattleNode::init() {
    audio["noise"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/start_noise"));
    audio["start"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/battleStart"));

    isStart = false;
    isGameStart = false;
    background->set_z_index(3);
    heart->set_z_index(4);
    heart->set_global_position(camera->get_global_position() - Vector2(window->get_size().width/3, 20));
}

void BattleNode::_process(double delta) {
    if(isStart) {
        background->set_z_index(-1);
        heart->set_z_index(0);
    }else if(!isStart) {
        start(delta); 
    }
}

void BattleNode::start(double delta) {
    if(cool <= 2) {
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
                times = 0;
                cool = 0;
                isStart = true;
            }else {
                times+=delta;
                background->set_z_index(5);
            }
        }
    }
}