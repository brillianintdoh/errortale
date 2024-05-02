#ifndef Part2_H
#define Part2_H
#include "../../main/env/main.h"
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/classes/resource_loader.hpp>
#include<godot_cpp/classes/json.hpp>
#include<godot_cpp/variant/variant.hpp>
#include<godot_cpp/classes/audio_stream.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
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

            void _ready() override;
            void _process(double delta) override;
        
        private:
            int isShake, json_index;
            double wait[4];
            double sleep_s, sleep_b;
            ResourceLoader *res;
            JSON *json;
            Variant data_json;
            TextureRect* background;
            AudioStreamPlayer* sound;
    };
}
#endif