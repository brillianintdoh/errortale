#ifndef Heart_H
#define Heart_H
#include<godot_cpp/classes/character_body2d.hpp>
namespace godot {
    class Heart : public CharacterBody2D {
        GDCLASS(Heart, CharacterBody2D);

        protected:
            static void _bind_methods();
        
        public:
            Heart();
            ~Heart();

            void _physics_process(double delta) override;
        
        private:
            Vector2 vec;
            float speed;
    };
}
#endif