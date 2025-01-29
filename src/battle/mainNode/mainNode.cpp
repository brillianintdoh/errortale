#include "mainNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/input.hpp>
using namespace godot;

BattleNode::BattleNode() {
    times = 0;
    is = 0;
    cool = 0;
    time_KARMA = 0;
    isGameStart = false;
    isSelect = true;
    isAttack = 2;
    db["is_heal"] = false;
    db["bI"] = 1;
    db["jI"] = 0;
    db["item_index"] = 0;
    part = 1;
    isMoveButton = true;
    isSong = true;
}

BattleNode::~BattleNode() {}

void BattleNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("music_next"), &BattleNode::music_next);
    ClassDB::bind_method(D_METHOD("animated_start_end"), &BattleNode::animated_start_end);
    ClassDB::bind_method(D_METHOD("attack_end"), &BattleNode::attack_end);
    ClassDB::bind_method(D_METHOD("update_menu3"), &BattleNode::update_menu3);
    ClassDB::bind_method(D_METHOD("song_loop"), &BattleNode::song_loop);
}

void BattleNode::_ready() {
    camera = Object::cast_to<Camera2D>(get_node_internal("camera"));
    sans = Object::cast_to<AnimatedSprite2D>(get_node_internal("sans"));
    background = Object::cast_to<TextureRect>(get_node_internal("background"));
    shader = Object::cast_to<TextureRect>(get_node_internal("shader"));
    heart = Object::cast_to<HeartNode>(get_node_internal("HeartNode"));
    sprite = Object::cast_to<Node2D>(get_node_internal("sprite"));
    buttons = Object::cast_to<Node2D>(get_node_internal("buttons"));
    hpBar = Object::cast_to<TextureProgressBar>(get_node_internal("ui/hpBar"));
    KR = Object::cast_to<TextureProgressBar>(get_node_internal("ui/KR"));
    hpText = Object::cast_to<Label>(get_node_internal("ui/hpText"));
    hurt = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/hurt"));
    frame = Object::cast_to<Sprite2D>(get_node_internal("frame"));
    clipRect = Object::cast_to<Control>(get_node_internal("frame/ClipRect"));
    menu_text = Object::cast_to<RichTextLabel>(get_node_internal("ui/menu_text"));
    impact = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/impact"));
    item_list = Object::cast_to<ItemList>(get_node_internal("ui/ItemList"));
    material = shader->get_material();
    window = get_window();
    KR_progress = KR->get_progress_texture();

    audio["noise"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/start_noise"));
    audio["start"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/battleStart"));
    audio["menu_move"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/menu_move"));
    audio["menu_select"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/menu_select"));
    audio["heal"] = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound/heal"));
    init();
}

int isS = 0, btnISCool = false;
double btnTime = 0, accpetTime = 0;
void BattleNode::_process(double delta) {
    if(isStart == 1) {
        background->set_z_index(-1);
        heart->set_z_index(0);
        sans->play("page_1");
        isStart = 2;
    }else if(!isStart) {
        start(delta); 
    }

    if(times >= 6.2 && isS == 1) {
        isS = 2;
        sans->set_speed_scale(1);
        sans->play("battle_start");
    }else {
        times+=delta;
    }

    // 카르마 및 데미지 피해
    if(isKARMA) {
        hpBar->set_value(HP);
        hpText->set_text("550 / "+String::num_int64(HP+KARMA));
        KR_progress->set_width(KARMA_empty ? KARMA_empty : 1);
        KR->set_max(KARMA_empty ? KARMA_empty : 1);
        KR->set_progress_texture(KR_progress);
        KR->set_value((KARMA / KARMA_empty) * KARMA_empty);

        if(KARMA <= 0) {
            isKARMA = false;
            KARMA = 0;
        }else {
            if(time_KARMA >= 0.3) {
                KARMA-=1;
                time_KARMA = 0;
            }else {
                time_KARMA+=delta;
            }
        }
    }

    // 내 턴
    if(isMyTurn) {
        Input& i = *Input::get_singleton();

        if(isMoveButton) {
            // 버튼 선택
            if(!isSelect) {
                if(btnISCool) {
                    btnTime+=delta;
                    if(btnTime >= 0.1) {
                        btnTime = 0;
                        btnISCool = false;
                    }
                }else {
                    btnISCool = true;
                    int input = i.is_action_pressed("ui_right") - i.is_action_pressed("ui_left");
                    int bI = db["bI"];
                    int num = bI+input;
                    if((num <= 4 && num > 0) && input != 0) {
                        Object::cast_to<Sprite2D>(buttons->get_node_internal("button_"+String::num(num)))->set_texture(btnON[num-1]);
                        Object::cast_to<Sprite2D>(buttons->get_node_internal("button_"+String::num(bI)))->set_texture(btn[bI-1]);
                        Object::cast_to<AudioStreamPlayer>(audio["menu_move"])->play();
                        db["bI"] = num;
                    }
                }
            }

            // 선택
            int bI = db["bI"];
            if(i.is_action_pressed("select") && accpetTime >= 0.2) {
                if(!isSelect) {
                    if(bI == 1) {
                        menu_1();
                        isSelect = true;
                        accpetTime = 0;
                    }else if(bI == 3) {
                        menu_3();
                        isSelect = true;
                        accpetTime = 0;
                    }

                    if(isSelect) {
                        int bI = db["bI"];
                        String num = String::num(bI);
                        Object::cast_to<Sprite2D>(buttons->get_node_internal("button_"+num))->set_texture(btn[bI-1]);
                        Object::cast_to<AudioStreamPlayer>(audio["menu_select"])->play();
                    }
                }else {
                    if(bI == 1 && !isAttack) {
                        isAttack = true;
                        accpetTime = 0;
                    }else if(bI == 3) {
                        use_3();
                        accpetTime = 0;
                    }
                }
            }else if(accpetTime < 0.2) accpetTime+=delta;

            // 선택 취소
            if(i.is_key_pressed(KEY_X) && isSelect) {
                menu_text->set_visible(true);
                menu_text->set_visible_ratio(0);
                Object::cast_to<Sprite2D>(buttons->get_node_internal("button_"+String::num(bI)))->set_texture(btnON[bI-1]);
                if(bI == 3) {
                    isSelect = false;
                    item_list->set_visible(false);
                    heart->set_visible(false);
                }
            }

            // menu 3 선택
            if(item_list->is_visible()) {
                int index = db["item_index"], isMove = false;
                if (i.is_action_just_pressed("ui_right")) {
                    index = min(index + 1, item_list->get_item_count() - 1);
                    isMove = true;
                }else if (i.is_action_just_pressed("ui_left")) {
                    index = max(index - 1, 0);
                    isMove = true;
                }

                if(isMove) {
                    db["item_index"] = index;
                    update_menu3();
                }
            }
        }

        // ui 대사 출력
        float ratio = menu_text->get_visible_ratio();
        if(ratio < 1) {
            if(times >= 0.1) {
                times = 0;
                menu_text->set_visible_ratio(ratio+(delta*1.5));
            }else times+=delta;
        }else {
            int is_heal = db["is_heal"];
            if(is_heal) {
                db["is_heal"] = false;
                sleep([this]() {
                    nextTurn();
                    isMoveButton = true;
                }, 1.3);
            }
        }
    }

    effects(delta);
    if(isGameStart) game(delta);
}

void BattleNode::start(double delta) {
    if(cool <= 1) {
        cool+=delta;
        if(times >= 0.2) {
            times = 0;
            background->set_z_index(3);
            Object::cast_to<AudioStreamPlayer>(audio["noise"])->play();
        }else {
            times += delta;
            background->set_z_index(5);
        }
    }else {
        if(!isS) {
            Object::cast_to<AudioStreamPlayer>(audio["start"])->play();
            isS = true;
        }

        Vector2 vec = heart->get_global_position();
        if(vec.x < -0.4 && vec.y < -0.4) {
            background->set_z_index(3);
            Vector2 new_pos = vec.lerp(Vector2(0,0), delta * 2);
            heart->set_global_position(new_pos);
            times = 0;
        }else {
            if(times >= 1) {
                camera_shake(6, 0.5, 0.5);
                times = 0;
                cool = 0;
                isStart = true;
                music_next();
            }else {
                times+=delta;
                background->set_z_index(5);
            }
        }
    }
}