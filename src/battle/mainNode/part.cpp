#include "mainNode.h"
#include "../../env/env.h"

void BattleNode::game(double delta) {
    if(part == 1) part1(delta);
    else if(part == 2) part2(delta);
}

double time1 = 0, is1 = 0;
vector<SansBone*> bones1;
void BattleNode::part1(double delta) {
    time1+=delta;
    if(time1 < 1) {
        if(is1 != 0) return;
        heart->set_blue(true, 10, 0);
        heart->set_coolTime(0.5);
        set_gasterBlaster(Vector2(882, 909), Vector2(3,3), -90, 0.2);
        is1= 1;
    }else if(time1 < 5.5) {
        if(is1 == 1) {
            set_bone1(Vector2(950.672, 33.335), Vector2(-600.193, 33.335), Vector2(1.5, 1), 0, 0.5);
            set_bone1(Vector2(1300.563, 130.427), Vector2(-830.275, 130.427), Vector2(1.5, 1), 180, 0.5);
            is1= 2;
        }else if(time1 >= 5) {
            if(is1 == 2) set_gasterBlaster(Vector2(heart->get_position().x-100, 1442), Vector2(5,5), 0, 2);
            heart->set_blue(false);
            is1 = 3;
        }
    }else if(time1 < 6) {
        if(is1 != 3) return;
        set_frame(Vector2(3, 4.405), true, [this]() {
            Vector2 scale = Vector2(1.5, 0.586);
            bones1.push_back(set_bone2(Vector2(263.333, 187.568), Vector2(199.333, 111.291), scale, 50, 1.5));
            bones1.push_back(set_bone2(Vector2(-2.667, 194.151), Vector2(69, 108.793), scale, -50, 1.5));
            bones1.push_back(set_bone2(Vector2(29, -35.815), Vector2(101.333, 50.451), scale, -50, 1.5));
            bones1.push_back(set_bone2(Vector2(246.333, -33.545), Vector2(176, 49.997), scale, 50, 1.5));
            is = 1;
        });
        bones1.push_back(set_bone2(Vector2(136.968, -16.291), Vector2(136.968, 82.687), Vector2(1.5, 1), 90, 0.4));
        is1 = 4;
    }else if(time1 < 9) {
        if(is == 1) {
            blackScene(0.3, [this]() {
                set_gasterBlaster(Vector2(-556, 347), Vector2(5,5), 142.8, 3, false);
                set_gasterBlaster(Vector2(680, 319), Vector2(5,5), 214.5, 3, false);
                set_gasterBlaster(Vector2(668, 691), Vector2(5,5), 236, 3, false);
                set_gasterBlaster(Vector2(-568, 631), Vector2(5,5), 147.8, 3, false);
                set_gasterBlaster(Vector2(-616, 971), Vector2(5,5), 92.5, 3, false);
                set_gasterBlaster(Vector2(632, 999), Vector2(5,5), 271.5, 3, false);
                sleep([this]() {
                    is = 3;
                }, 1.5);
            });
            is = 2;
        }
    }else if(time1 < 11) {
        if(is == 3) {
            for(SansBone* bone : bones1) bone->queue_free();
            blackScene(2.5, [this]() { nextTurn(); });
            is = 4;
        }
    }
}

double time2 = 0, is2 = 0;
void BattleNode::part2(double delta) {
    if(is2 == 0) {
        is2 = 1;
        heart->set_position(Vector2(0,0));
        camera_angle(80);
        set_frame(Vector2(449.5, 0), false, [](){}, 2.5);
        set_frame(Vector2(2.489, 4.405), true, [this](){
            set_bone3(Vector2(1.992, -58.289), Vector2(1.15, 1), 10);
            heart->set_blue(true);

            sleep([this]() {
                heart->set_blue(true, 0, -10);
                sleep([this]() {
                    heart->set_blue(true);
                    sleep([this]() {
                        heart->set_blue(true, 0, -10);
                        heart->set_coolTime(0.2);
                        is = 1;
                    },2);
                },3);
            },3);
        }, 2.5);
    }else if(is == 1) {
        is = 2;
        sleep([this]() {
            Vector2 scale = Vector2(1.8,1);
            set_bone2(Vector2(332.346, -180.65), Vector2(-52.034, -51.865), scale, 0, 1, true);
            set_bone2(Vector2(-32.034, -180.65), Vector2(320, -51.865), scale, 0, 1, true);
            sleep([this]() {
                heart->set_blue(true, -10, 0);
                Vector2 scale = Vector2(3,3);
                set_gasterBlaster(Vector2(-8, 364), scale, 140);
                set_gasterBlaster(Vector2(30, 1301), scale, 47);
            },1);
        }, 3.3);
    }
}