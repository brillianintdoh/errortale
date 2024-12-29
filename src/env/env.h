#ifndef ENV_H
#define ENV_H
#include<godot_cpp/classes/camera2d.hpp>
#include<godot_cpp/classes/window.hpp>
using namespace godot;

extern Camera2D* camera;
extern Window* window;
extern int isStart, isBattle;

#endif