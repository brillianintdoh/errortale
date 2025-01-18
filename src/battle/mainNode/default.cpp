#include "mainNode.h"
#include "../../env/env.h"

void BattleNode::nextTurn() {
    buttons->set_visible(!isMyTurn);
    menu_text->set_visible(!isMyTurn);
    heart->set_visible(isMyTurn);
    if(isMyTurn) {
        menu_text->set_visible_ratio(0);
        isMyTurn = false;
        is = 0;
        part++;
    }else {
        set_frame(Vector2(0, 0), false, [](){}, 3);
        set_frame(Vector2(7, 4.305), true, [this]() {
            int index = db["jI"];
            String text;
            if(json_text.size() > index) {
                text = json_text[index].get("text");
                index++;
            }else text = "계속 공격하자";
            db["jI"] = index;
            menu_text->set_text("* "+text);
        }, 3);
        int bI = db["bI"];
        String num = String::num(bI);
        Object::cast_to<Sprite2D>(buttons->get_node_internal("button_"+num))->set_texture(btn[bI-1]);
        Object::cast_to<Sprite2D>(buttons->get_node_internal("button_1"))->set_texture(btnON[0]);
        db["bI"] = 1;
        isSelect = false;
        isMyTurn = true;
    }
}