#ifndef MainNode_H
#define MainNode_H
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/sprite2d.hpp>
#include<godot_cpp/classes/control.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/classes/resource_loader.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
#include<godot_cpp/classes/label.hpp>
namespace godot {
    class MainNode : public Node2D {
        GDCLASS(MainNode, Node2D);

        protected:
            static void _bind_methods();

        private:
            int isON;
            double start_time;
            Sprite2D* title;
            TextureRect* background;
            TextureRect* shader;
            ResourceLoader* resource_loader;
            AudioStreamPlayer* logoPlay;
            Sprite2D* sans;
            Sprite2D* gameTitle;
            Label* btn1;
            Label* btn2;
            std::vector<Ref<Texture2D>> res;

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