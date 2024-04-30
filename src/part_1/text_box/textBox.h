#ifndef TextBox_H
#define TextBox_H
#include "../../main/env/main.h"
#include<godot_cpp/classes/control.hpp>
#include<godot_cpp/classes/rich_text_label.hpp>
#include<godot_cpp/classes/json.hpp>
#include<godot_cpp/variant/variant.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
namespace godot {
    class TextBox : public Control {
        GDCLASS(TextBox, Control);

        protected:
            static void _bind_methods();
        
        public:
            TextBox();
            ~TextBox();
            void text_next();
            void startSound_end();

            void _process(double delta) override;
            void _ready() override;

        private:
            int ni, isNext, isStart;
            double length, time;
            AudioStreamPlayer* startSound;
            RichTextLabel* text;
            Variant sans_data;
            JSON *json;
    };
}
#endif