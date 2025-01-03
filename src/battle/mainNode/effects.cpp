#include "mainNode.h"
#include "../../env/env.h"

void BattleNode::shake_camera(double cool, float stre, float dur) {
    shakeCool = cool;
    shake = stre;
    shakeDur = dur;

    shakeTime[0] = 0;
    shakeTime[1] = 0;
}

void BattleNode::backScene(double cool) {
    backCool = cool;
    backTime = 0;
}

void BattleNode::effects(double delta) {
    if(backCool != 0) {
        background->set_z_index(3);
        if(backTime >= backCool) {
            background->set_z_index(-1);
            backCool = 0;
            backIs = true;
        }else {
            backTime+=delta;
        }
    }else if(backIs) {
        backIs = false;
        heart->set_blue(true);
    }

    if(shakeCool != 0) {
        if(shakeTime[0] >= shakeCool) {
            printf("w\n");
            is_shaking = true;
            shakeCool = 0;
            camera->set_drag_horizontal_offset(0);
            camera->set_drag_vertical_offset(0);
        }else {
            shakeTime[1] += delta;
            if(shakeTime[1] <= shakeDur*1) {
                camera->set_drag_horizontal_offset(shake);
                camera->set_drag_vertical_offset(shake);
            }else if(shakeTime[1] <= shakeDur*1.2) {
                camera->set_drag_horizontal_offset(-shake);
                camera->set_drag_vertical_offset(-shake);
            }else if(shakeTime[1] <= shakeDur*1.3) {
                camera->set_drag_horizontal_offset(shake);
                camera->set_drag_vertical_offset(-shake);
            }else if(shakeTime[1] <= shakeDur*1.4) {
                camera->set_drag_horizontal_offset(-shake);
                camera->set_drag_vertical_offset(shake);
                shakeTime[1] = 0;
            }
            shakeTime[0] += delta;
        }
    }else if(is_shaking) {
        is_shaking = false;
    }
}