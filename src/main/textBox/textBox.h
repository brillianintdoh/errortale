#ifndef TextBox_H
#define TextBox_H
#include<godot_cpp/classes/control.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/classes/rich_text_label.hpp>
namespace godot {
    class TextBox : public Control {
        GDCLASS(TextBox, Control);

        protected:
            static void _bind_methods();

        private:
            TextureRect* head;
            RichTextLabel* text;

        public:
            TextBox();
            ~TextBox();

            void _process(double delta) override;
            void _ready() override;
    };
}

#endif