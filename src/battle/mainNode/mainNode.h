#ifndef BattleNode_H
#define BattleNode_H
#include "../heartNode/heartNode.h"
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
#include<godot_cpp/variant/dictionary.hpp>
namespace godot {
    class BattleNode : public Node2D {
        GDCLASS(BattleNode, Node2D);

        protected:
            static void _bind_methods();

        private:
            Dictionary audio, music, sprite;
            AnimatedSprite2D* sans;
            TextureRect* background;
            HeartNode* heart;

            double times, cool;
            double backTime, backCool, shakeTime[2], shakeCool;
            float shake, shakeDur;
            int backIs, is_shaking;
            int is;
        
        public:
            BattleNode();
            ~BattleNode();

            void _process(double delta) override;
            void _ready() override;

            void effects(double delta);

            void shake_camera(double cool, float stre=0.5, float dur=0.3);
            void backScene(double cool);

            void start(double delta);
            void init();

            void animated_start_end();
            void music_start_end();
    };
}

#endif