#include "mainNode.h"
#include "../../env/env.h"
#include<godot_cpp/classes/resource_loader.hpp>
#include<godot_cpp/classes/file_access.hpp>
#include<godot_cpp/classes/json.hpp>

void BattleNode::init() {
    ResourceLoader* loader = ResourceLoader::get_singleton();
    for(int i=1; i <= 4; i++) {
        String num = String::num(i);
        Ref<Texture2D> texture = loader->load("res://assets/button/battle/"+num+".png");
        Ref<Texture2D> texture_on = loader->load("res://assets/button/battle/"+num+"_.png");
        btn.push_back(texture);
        btnON.push_back(texture_on);
    }
    Ref<FileAccess> text_file = FileAccess::open("res://data/text.json", FileAccess::READ);
    Ref<FileAccess> item_file = FileAccess::open("res://data/items.json", FileAccess::READ);
    json_text = JSON::parse_string(text_file->get_as_text());
    json_item = JSON::parse_string(item_file->get_as_text());
    for(int i=0; i < json_item.size(); i++) {
        item_list->add_item(json_item[i].get("name"));
    }
    db["song"] = 0;
    songs.push_back(Object::cast_to<Node2D>(get_node_internal("song/start")));
    songs.push_back(Object::cast_to<Node2D>(get_node_internal("song/sans")));

    isStart = false;
    background->set_z_index(3);
    heart->set_z_index(4);
    heart->set_global_position(camera->get_global_position() - Vector2(window->get_size().width, 20));
    sans->play("page_1");
    sans->stop();
    sans->set_frame(0);
}

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