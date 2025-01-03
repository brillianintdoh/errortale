#include "mainNode.h"
#include "../../env/env.h"

void BattleNode::music_start_end() {
    Object::cast_to<AudioStreamPlayer>(music["sans"])->play();
}

void BattleNode::animated_start_end() {
    sans->set_speed_scale(2.5);
    sans->play("page_1");
    backScene(1.3);
}