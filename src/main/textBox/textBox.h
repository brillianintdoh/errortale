#ifndef TextBox_H
#define TextBox_H
#include<godot_cpp/classes/control.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/classes/rich_text_label.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
namespace godot {
    class TextBox : public Control {
        GDCLASS(TextBox, Control);

        protected:
            static void _bind_methods();

        private:
            std::vector<Ref<Texture2D>> heads;
            TextureRect* head;
            RichTextLabel* text;
            Variant json;
            AnimatedSprite2D* error_start;
            int lenght, index, isFirst, time;
            double times;

        public:
            TextBox();
            ~TextBox();

            void _process(double delta) override;
            void _ready() override;

            void nextText();
    };
}

#endif