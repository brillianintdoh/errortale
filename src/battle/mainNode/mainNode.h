#ifndef BattleNode_H
#define BattleNode_H
#include "../heartNode/heartNode.h"
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/variant/dictionary.hpp>
namespace godot {
    class BattleNode : public Node2D {
        GDCLASS(BattleNode, Node2D);

        protected:
            static void _bind_methods();

        private:
            Dictionary audio;
            AnimatedSprite2D* sans;
            TextureRect* background;
            HeartNode* heart;

            double times, cool;
            int is;
        
        public:
            BattleNode();
            ~BattleNode();

            void _process(double delta) override;
            void _ready() override;

            void start(double delta);
            void init();
    };
}

#endif