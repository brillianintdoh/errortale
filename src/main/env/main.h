#ifndef MAIN1_H
#define MAIN1_H
#include<godot_cpp/classes/camera2d.hpp>
#include<godot_cpp/classes/character_body2d.hpp>
using namespace godot;

// 메인 변수
extern int isPath1;
extern int isPath2;
extern Camera2D* camera;
extern CharacterBody2D* user;

// part_1 env 변수
extern int isBattle;
extern int isSans;
extern int isBattle_start;
#endif