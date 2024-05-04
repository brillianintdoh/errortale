#ifndef Part2_H
#define Part2_H
#include "../../main/env/main.h"
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/rich_text_label.hpp>
#include<godot_cpp/classes/control.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/classes/resource_loader.hpp>
#include<godot_cpp/classes/json.hpp>
#include<godot_cpp/variant/variant.hpp>
#include<godot_cpp/classes/audio_stream.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
namespace godot {
    class Part2 : public Node2D {
        GDCLASS(Part2, Node2D);

        protected:
            static void _bind_methods();

        public:
            Part2();
            ~Part2();
            void shake(double delta);
            void black_scene(double delta);
            void sound_end();
            void sansAnim_end();

            void _ready() override;
            void _process(double delta) override;
        
        private:
            int isShake, isBlack, json_index;
            double wait[4];
            double sleep_s, sleep_b;
            ResourceLoader *res;
            JSON *json;
            Variant data_json;
            Variant tools_json;
            Control* tools_menu;
            RichTextLabel* tools[8];
            TextureRect* background;
            AudioStreamPlayer* sound;
            AnimatedSprite2D* sans;
            Node2D* ui;
    };
}
#endif