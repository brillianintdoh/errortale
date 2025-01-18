#include "mainNode.h"
#include "../../env/env.h"

// 공격 메뉴
void BattleNode::menu_1() {
    Sprite2D* attack_ui = Object::cast_to<Sprite2D>(get_node_internal("ui/attack_ui"));
    AnimatedSprite2D* bar = Object::cast_to<AnimatedSprite2D>(attack_ui->get_node_internal("bar"));
    isAttack = false;
    attack_ui->set_visible(true);
    menu_text->set_visible(false);
    loop([this, attack_ui, bar](double delta) {
        Vector2 scale = attack_ui->get_scale().lerp(Vector2(3.278, 4.396), delta*100);
        attack_ui->set_scale(scale);
        int isloop = false;
        if(isAttack) {
            bar->play();
            isloop = true;
            AnimatedSprite2D* attack = Object::cast_to<AnimatedSprite2D>(get_node_internal("sans/attack"));
            attack->set_visible(true);
            attack->play();
            sleep([this, attack_ui, bar, attack]() {
                isAttack = 2;
                bar->stop();
                attack_ui->set_visible(false);
                attack_ui->set_scale(Vector2(0.1, 4.396));
                bar->set_position(Vector2(-265, 0));
                attack->set_visible(false);
                nextTurn();
            }, 5);
        }else {
            Vector2 vec = bar->get_position().lerp(Vector2(265,0), delta*1.3);
            bar->set_position(vec);
            if(vec.distance_to(Vector2(265,0)) < 0.2) {
                isloop = true;
                isAttack = 2;
                attack_ui->set_visible(false);
                attack_ui->set_scale(Vector2(0.1, 4.396));
                nextTurn();
                bar->set_position(Vector2(-265, 0));
            }
        }
        return isloop || isAttack;
    });
}

// 아이템 메뉴
void BattleNode::menu_3() {
    menu_text->set_visible(false);
    item_list->set_visible(true);
    heart->set_visible(true);
    db["itme_index"] = 0;
    isSelect = false;
    call_deferred("update_menu3");
}
void BattleNode::use_3() {
    int index = db["item_index"];
    double hp = json_item[index].get("hp");
    String name = json_item[index].get("name");
    String text = json_item[index].get("text");
    text = text.length() > 0 ? "\n"+text : text;
    if(HP+hp >= HP_MAX) {
        HP = HP_MAX;
        text += String::utf8("\n* HP가 가득찼다");
    }else {
        HP+=hp;
        String t = String::utf8("\n* HP를 +");
        t += String::num_int64(hp);
        t += String::utf8("를 회복했다");
        text += t;
    }
    if(isKARMA) {
        if(HP == HP_MAX) {
            HP-=KARMA;
            KARMA_empty=KARMA;
        }else {
            HP-=KARMA;
            KARMA_empty = (HP_MAX-HP);
        }
    }else {
        KARMA_empty = (HP_MAX-HP);
        isKARMA = true;
    }
    item_list->set_visible(false);
    item_list->remove_item(index);

    Array new_items;
    for(int i=0; i < json_item.size(); i++) {
        if(i != index) new_items.push_back(json_item[i]);
    }
    json_item = new_items;
    menu_text->set_text(String::utf8("* 당신은 ")+name+String::utf8("를(을) 사용했다")+text);
    menu_text->set_visible_ratio(0);
    menu_text->set_visible(true);
    heart->set_visible(false);
    
    Object::cast_to<AudioStreamPlayer>(audio["heal"])->play();
    db["is_heal"] = true;
    isMoveButton = false;
}
void BattleNode::update_menu3() {
    int index = db["item_index"];
    Rect2 item_rect = item_list->get_item_rect(index);
    Vector2 new_pos = item_list->get_position() + Vector2(item_rect.position.x - 50, item_rect.position.y + item_rect.size.y/2);
    heart->set_position(new_pos);
}