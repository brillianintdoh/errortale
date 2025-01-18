#include "gasterBlaster.h"
#include "../../../env/env.h"

GasterBlaster::GasterBlaster() {
    cool = 3;
    time = 0;
    isEnd = 0;
    cool = 0.3;
}

GasterBlaster::~GasterBlaster() {}

void GasterBlaster::_bind_methods() {
    ClassDB::bind_method(D_METHOD("end"), &GasterBlaster::end);
}

void GasterBlaster::_ready() {
    connect("animation_finished", Callable(this, "end"));
    beam = Object::cast_to<Sprite2D>(get_node_internal("beam"));
    beam_collision = Object::cast_to<CollisionShape2D>(get_node_internal("beam/beam_body/beam_collision"));
    sound = Object::cast_to<AudioStreamPlayer>(get_node_internal("sound"));
    beam->set_visible(false);
    beam_collision->set_disabled(true);
    time = 0;
    isEnd = 0;
    beam_phase = 0;
    isLaunch = false;
    
    if(isGameStart) Object::cast_to<AudioStreamPlayer>(get_node_internal("ready"))->play();
}

void GasterBlaster::_process(double delta) {
    if(isEnd) return;
    if(is_playing()) {
        if(get_frame() == 8) {
            beam->set_visible(true);
            stop();
            set_frame(8);
            sound->play();
        }
    }
    
    if(beam->is_visible()) {
        isLaunch = true;
        beam_collision->set_disabled(false);
        Vector2 scale = beam->get_scale();
        Vector2 vec = get_scale();

        Vector2 target_scale = Vector2(vec.x/1.7, scale.y);
        Vector2 zero_scale = Vector2(0, scale.y);
        Vector2 half_scale = Vector2(target_scale.x * 0.5, scale.y);

        float oscillation = (sin(beam_phase * Math_PI * 2.0f) + 1.0f) * 0.5f;
        float current_scale = (vec.x/2) * (0.5f + oscillation * 0.5f);
        scale.x = current_scale;
        beam_phase += delta;
        beam->set_scale(scale);
    }

    if(cool <= time && isLaunch) {
        beam->queue_free();
        play();
        isEnd = 1;
    }else if(isLaunch) time += delta;
}

void GasterBlaster::end() {
    queue_free();
}

void GasterBlaster::setCoolTime(float coolTime) {
    cool = coolTime;
}

void GasterBlaster::setLaunch(int is) {
    isLaunch = is;
}