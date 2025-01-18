#include "attackBody.h"
#include "../../../env/env.h"

AttackBody::AttackBody() {}

AttackBody::~AttackBody() {}

void AttackBody::_bind_methods() {
    ClassDB::bind_method(D_METHOD("onCollision", "node"), &AttackBody::onCollision);
}

void AttackBody::_ready() {
    connect("body_entered", Callable(this , "onCollision"));
}

void AttackBody::_physics_process(double delta) {
    TypedArray<Node2D> bodies = get_overlapping_bodies();
    
    for(int i=0; i < bodies.size(); i++) {
        Node2D* node = Object::cast_to<Node2D>(bodies[i]);
        String name = node->get_name().to_utf8_buffer().get_string_from_utf8();
        if(name == "HeartNode") {
            hurt->play();
            if(HP == 1) {
                if(KARMA != 0) {
                    KARMA-=1;
                }else {
                    printf("game over\n");
                }
            }else {
                KARMA+=1;
                HP-=1;
                KARMA_empty+=1;
                isKARMA = true;
            }
        }
    }
}

void AttackBody::onCollision(Node* node) {
    String name = node->get_name().to_utf8_buffer().get_string_from_utf8();
    if(name == "HeartNode") {
        hurt->play();
        if(HP == 1 && KARMA != 0) {
            KARMA-=1;
        }else if(HP != 1) {
            HP-=1;
        }else {
            printf("game over\n");
        }
    }
}