#ifndef PATE_1_H
#define PATH_1_H
#include "../../main/env/main.h"
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/classes/sprite2d.hpp>
#include<godot_cpp/classes/control.hpp>

namespace godot {
    class Part1 : public Node2D {
        GDCLASS(Part1, Node2D);

        public:
            Part1();
            ~Part1();
            void battle_start();
            void shake(double delta);

            void _process(double delta) override;
            void _ready() override;

        protected:
            static void _bind_methods();

        private:
            TextureRect* background;
            Sprite2D* sans;
            Sprite2D* last_corridor;
            Sprite2D* heart;
            Control* text_box;
            double wait, slep;
            int wait_i, start, wait_stop, start_part;
    };
}
#endif