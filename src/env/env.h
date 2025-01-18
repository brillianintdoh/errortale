#ifndef ENV_H
#define ENV_H
#define HP_MAX 550 
#include<godot_cpp/classes/camera2d.hpp>
#include<godot_cpp/classes/window.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
using namespace godot;

extern Camera2D* camera;
extern Window* window;
extern AudioStreamPlayer* hurt;
extern AudioStreamPlayer* impact;
extern double HP, KARMA, KARMA_empty;
extern int isStart, isSans, isGameStart, isKARMA, isMyTurn;

#endif