#include "mainNode.h"
#include "../../env/env.h"

void BattleNode::music_next() {
    int song = db["song"];
    songs[song++]->call("play");
    db["song"] = song;
}

void BattleNode::animated_start_end() {
    sans->set_speed_scale(2.5);
    sans->play("page_1");
    blackScene(1.3, []() {
        isGameStart = true;
    });
}

void BattleNode::attack_end() {
    set_shader(3.6, 0.3, 0.5, 5, 0.15);
}

void BattleNode::song_loop() {
}