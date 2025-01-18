#ifndef SansBone_H
#define SansBone_H
#include<godot_cpp/classes/sprite2d.hpp>
namespace godot {
    class SansBone : public Sprite2D {
        GDCLASS(SansBone, Sprite2D);

        protected:
            static void _bind_methods();

        private:
            Vector2 target;
            double speed;
            int is, isON;
        
        public:
            SansBone();
            ~SansBone();

            void _process(double delta) override;
            void _ready() override;

            void set_target(Vector2 vec, double speed, int on=true);
    };
}

#endif