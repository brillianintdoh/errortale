#ifndef MainNode_H
#define MainNode_H
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/sprite2d.hpp>
#include<godot_cpp/classes/control.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
namespace godot {
    class MainNode : public Node2D {
        GDCLASS(MainNode, Node2D);

        protected:
            static void _bind_methods();

        private:
            int btn_lengtn, isON, btnI;
            double start_time;
            std::vector<Sprite2D*> btns;
            std::vector<Ref<Texture2D>> res;
            std::vector<Ref<Texture2D>> resOn;
            Sprite2D* title;
            Control* ui;
            AnimatedSprite2D* effect;
            TextureRect* background;
            Sprite2D* sans;

        public:
            MainNode();
            ~MainNode();

            void _process(double delta) override;
            void _ready() override;

            void init();
            void on(double delta);
    };
}

#endif