#ifndef HeartNode_H
#define HeartNode_H
#include<godot_cpp/classes/character_body2d.hpp>
namespace godot {
    class HeartNode : public CharacterBody2D {
        GDCLASS(HeartNode, CharacterBody2D);

        protected:
            static void _bind_methods();
        
        public:
            HeartNode();
            ~HeartNode();

            void _physics_process(double delta) override;
            void _ready() override;
    };
}

#endif