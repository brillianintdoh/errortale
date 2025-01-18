#ifndef AttackBody_H
#define AttackBody_H
#include<godot_cpp/classes/area2d.hpp>
namespace godot {
    class AttackBody : public Area2D {
        GDCLASS(AttackBody, Area2D);

        protected:
            static void _bind_methods();

        public:
            AttackBody();
            ~AttackBody();

            void _ready() override;
            void _physics_process(double delta) override;

            void onCollision(Node* node);
    };
}

#endif