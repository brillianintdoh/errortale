#ifndef UserNode_H
#define UserNode_H
#include<godot_cpp/classes/character_body2d.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
namespace godot {
    class UserNode : public CharacterBody2D {
        GDCLASS(UserNode, CharacterBody2D);

        protected:
            static void _bind_methods();
        
        private:
            AnimatedSprite2D* animated;
            int isMove;
            double start_time;
        
        public:
            UserNode();
            ~UserNode();

            void _physics_process(double delta) override;
            void _ready() override;
    };
}

#endif