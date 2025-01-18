#ifndef GasterBlaster_H
#define GasterBlaster_H
#include<godot_cpp/classes/animated_sprite2d.hpp>
#include<godot_cpp/classes/sprite2d.hpp>
#include<godot_cpp/classes/collision_shape2d.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
namespace godot {
    class GasterBlaster : public AnimatedSprite2D {
        GDCLASS(GasterBlaster, AnimatedSprite2D);

        protected:
            static void _bind_methods();

        private:
            Sprite2D* beam;
            CollisionShape2D* beam_collision;
            AudioStreamPlayer* sound;
            float cool, beam_phase;
            double time;
            int isEnd, isLaunch;

        public:
            GasterBlaster();
            ~GasterBlaster();

            void _process(double delta) override;
            void _ready() override;

            void end();

            void setCoolTime(float coolTime);
            void setLaunch(int is);
    };
}

#endif