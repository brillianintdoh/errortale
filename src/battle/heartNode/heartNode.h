#ifndef HeartNode_H
#define HeartNode_H
#include<godot_cpp/classes/rigid_body2d.hpp>
#include<godot_cpp/variant/dictionary.hpp>
#include<godot_cpp/classes/sprite2d.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
namespace godot {
    class HeartNode : public RigidBody2D {
        GDCLASS(HeartNode, RigidBody2D);

        protected:
            static void _bind_methods();

        private:
            String ui_direction;
            Dictionary hearts;
            Vector2 gravity;
            Sprite2D* sprite;
            AudioStreamPlayer* bell;
            int isBlue, isUP;
            double times, cool;

        public:
            HeartNode();
            ~HeartNode();

            void onCollision(Node* node);

            void _physics_process(double delta) override;
            void _ready() override;

            void set_blue(int is, int x=0, int y=10);
            void set_coolTime(double time);
    };
}

#endif