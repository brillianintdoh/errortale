#include "mainNode.h"
#include "../../env/env.h"

double shakeTime[2] = {0,0}, shakeCool = 0;
float shake = 0, shakeDur = 0;
int is_shaking = false;
function<void()> shakeFun;
void BattleNode::camera_shake(double cool, float stre, float dur, function<void()> fun) {
    shakeCool = cool;
    shake = stre;
    shakeDur = dur;
    shakeTime[0] = 0;
    shakeTime[1] = 0;
    shakeFun = fun;
}

double angleSpeed = 0, angleTarget = 0;
void BattleNode::camera_angle(double angle, double speed) {
    angleSpeed = speed;
    angleTarget = angle;
}

double blackTime = 0, blackCool = 0;
int blackIs = false;
function<void()> backFun;
void BattleNode::blackScene(double cool, function<void()> fun) {
    blackCool = cool;
    blackTime = 0;
    backFun = fun;
}

vector<double> frameSpeed;
vector<int> frameType;
vector<function<void()>> frameFuns;
// vector<Vector2> frameVecs; # vec 배열 변수 //
void BattleNode::set_frame(Vector2 vec, int type, function<void()> fun, double speed) {
    int lenght = frameFuns.size();
    frameVecs.push_back(vec);
    frameSpeed.push_back(speed);
    frameFuns.push_back(fun);
    frameType.push_back(type);
}

vector<function<void()>> sleepFuns;
vector<double> sleepCool, sleepTime;
void BattleNode::sleep(function<void()> fun, double cool) {
    sleepFuns.push_back(fun);
    sleepCool.push_back(cool);
    sleepTime.push_back(0);
}

vector<function<int(double delta)>> loopFuns;
int isLoop = false;
void BattleNode::loop(function<int(double delta)> fun) {
    loopFuns.push_back(fun);
    isLoop = true;
}

double shaderCool = 0, shaderTime = 0;
void BattleNode::set_shader(double cool, double shake_power, double shake_rate, double speed, double color_rate) {
    shaderCool = cool;
    shaderTime = 0;
    material->set_shader_parameter("shake_power", shake_power);
    material->set_shader_parameter("shake_rate", shake_rate);
    material->set_shader_parameter("shake_speed", speed);
    material->set_shader_parameter("shake_color_rate", color_rate);
    shader->set_material(material);
    shader->set_visible(true);
}

void BattleNode::effects(double delta) {
    if(blackCool != 0) {
        background->set_z_index(3);
        if(blackTime >= blackCool) {
            background->set_z_index(-1);
            blackCool = 0;
            blackIs = true;
        }else {
            blackTime+=delta;
        }
    }else if(blackIs) {
        blackIs = false;
        backFun();
    }

    if(shakeCool != 0) {
        if(shakeTime[0] >= shakeCool) {
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
        shakeFun();
    }

    if(shaderCool != 0) {
        if(shaderTime >= shaderCool) {
            shader->set_visible(false);
            shaderCool = 0;
        }else shaderTime+=delta;
    }

    if(angleSpeed != 0) {
        double rotation = camera->get_rotation_degrees();
        double new_rotation = Math::lerp(rotation, angleTarget, delta * angleSpeed);
        camera->set_rotation_degrees(new_rotation);
    
        if(Math::abs(new_rotation - angleTarget) < 0.1f) {
            angleSpeed = 0; 
        }
    }

    int i1 = 0;
    for(auto fun : sleepFuns) {
        if(sleepCool[i1] <= sleepTime[i1]) {
            fun();
            sleepCool.erase(sleepCool.begin() + i1);
            sleepTime.erase(sleepTime.begin() + i1);
            sleepFuns.erase(sleepFuns.begin() + i1);
        }else {
            sleepTime[i1]+=delta;
            i1++;
        }
    }

    int i2 = 0;
    for(auto fun : loopFuns) {
        if(fun(delta)) 
            loopFuns.erase(loopFuns.begin() + i2);
        else i2++;
    }

    int i3 = 0;
    for(auto fun : frameFuns) {
        int is = frameType[i3];
        double speed = frameSpeed[i3];
        Vector2 target = frameVecs[i3];
        Vector2 new_vec;
        if(is) {
            new_vec = frame->get_scale().lerp(target, delta*speed);
            frame->set_scale(new_vec);
        }else {
            new_vec = frame->get_position().lerp(target, delta*speed);
            frame->set_position(new_vec);
        }

        if(new_vec.distance_to(target) < 0.1) {
            fun();
            frameFuns.erase(frameFuns.begin() + i3);
            frameSpeed.erase(frameSpeed.begin() + i3);
            frameType.erase(frameType.begin() + i3);
            frameVecs.erase(frameVecs.begin() + i3);
        }else {
            i3++;
        }
    }
}