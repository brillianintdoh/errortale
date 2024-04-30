#ifndef UserNode_h
#define UserNode_h
#include "../../main/env/main.h"
#include<godot_cpp/classes/character_body2d.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
namespace godot {
    class userNode : public CharacterBody2D {
        GDCLASS(userNode, CharacterBody2D);

        protected:
            static void _bind_methods();
        
        public:
            userNode();
            ~userNode();

            void _physics_process(double delta) override;
            void _ready() override;
        
        private:
            float speed;
            Vector2 vec;
            AnimatedSprite2D* user;
            int battle;
    };
}
#endif