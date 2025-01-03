#ifndef HeartNode_H
#define HeartNode_H
#include <godot_cpp/classes/rigid_body2d.hpp>
#include<godot_cpp/variant/dictionary.hpp>
#include<godot_cpp/classes/sprite2d.hpp>
#include<godot_cpp/classes/texture_progress_bar.hpp>
namespace godot {
    class HeartNode : public RigidBody2D {
        GDCLASS(HeartNode, RigidBody2D);

        protected:
            static void _bind_methods();

        private:
            Dictionary hearts;
            Vector2 gravity;
            Sprite2D* sprite;
            TextureProgressBar* hpBar;
            int isBlue, isUP;
            double times;

        public:
            HeartNode();
            ~HeartNode();

            void onCollision(Node* node);

            void _physics_process(double delta) override;
            void _ready() override;

            void set_blue(int is, int x=0, int y=20);
    };
}

#endif