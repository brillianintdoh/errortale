#include "env.h"
Camera2D* camera = nullptr;
Window* window = nullptr;
AudioStreamPlayer* hurt = nullptr;
AudioStreamPlayer* impact = nullptr;
double HP = HP_MAX, KARMA = 0, KARMA_empty = 0;
int isStart = false, isSans = false, isGameStart = false, isKARMA = false, isMyTurn = false;