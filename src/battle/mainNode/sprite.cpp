#include "mainNode.h"
#include "../../env/env.h"
#include "../attack/gasterBlaster/gasterBlaster.h"
#include<godot_cpp/classes/path_follow2d.hpp>

void BattleNode::set_gasterBlaster(Vector2 pos, Vector2 scale, float angle, float cool, int isLaunch) {
    Node* node = Object::cast_to<GasterBlaster>(get_node_internal("sprite/GasterBlaster"))->duplicate();
    sprite->add_child(node);
    GasterBlaster* gaster_blaster = Object::cast_to<GasterBlaster>(node);
    gaster_blaster->set_scale(scale);
    gaster_blaster->set_position(pos);
    gaster_blaster->set_rotation(angle);
    gaster_blaster->set_rotation_degrees(angle);
    gaster_blaster->setCoolTime(cool);
    if(isLaunch) {
        gaster_blaster->play();
    }else {
        gaster_blaster->setLaunch(true);
        gaster_blaster->set_frame(7);
    }
}

void BattleNode::set_bone1(Vector2 pos, Vector2 target, Vector2 scale, float angle, float speed) {
    Node* node = Object::cast_to<SansBone>(get_node_internal("sprite/bone_1"))->duplicate();
    clipRect->add_child(node);
    SansBone* bone = Object::cast_to<SansBone>(node);
    bone->set_position(pos);
    bone->set_scale(scale);
    bone->set_rotation_degrees(angle);
    bone->set_target(target, speed);
}

SansBone* BattleNode::set_bone2(Vector2 pos, Vector2 target, Vector2 scale, float angle, float speed, int is) {
    Node* node = Object::cast_to<SansBone>(get_node_internal("sprite/bone_2"))->duplicate();
    clipRect->add_child(node);
    SansBone* bone = Object::cast_to<SansBone>(node);
    bone->set_position(pos);
    bone->set_scale(scale);
    bone->set_rotation_degrees(angle);
    bone->set_target(target, speed, is);

    return bone;
}

void BattleNode::set_bone3(Vector2 pos, Vector2 scale, double cool, float angle, float speed) {
    Node* node = Object::cast_to<Control>(get_node_internal("sprite/bone_3"))->duplicate();
    clipRect->add_child(node);
    PathFollow2D* sprite = Object::cast_to<PathFollow2D>(node->get_node_internal("path/bone"));
    Control* bone = Object::cast_to<Control>(node);
    bone->set_position(pos);
    bone->set_scale(scale);
    bone->set_rotation_degrees(angle);
    loop([this, speed, cool, sprite, bone](double delta) {
        static double time = 0;
        time+=delta;
        float prog = sprite->get_progress_ratio()+(delta*speed);
        sprite->set_progress_ratio(prog);

        if(time >= cool) {
            bone->queue_free();
            return true;
        }else {
            return false;
        }
    });
}