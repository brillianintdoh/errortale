#include "part1.h"
#include "part1_type.h"
#include<gdextension_interface.h>
#include<godot_cpp/core/defs.hpp>
#include<godot_cpp/godot.hpp>
using namespace godot;

void part1_init(ModuleInitializationLevel p_level) {
    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    ClassDB::register_class<Part1>();
}

void part1_uninit(ModuleInitializationLevel p_level) {
    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT part1_main_init(GDExtensionInterfaceGetProcAddress p_get, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_init) {
        GDExtensionBinding::InitObject init_obj(p_get, p_library, r_init);
        init_obj.register_initializer(part1_init);
        init_obj.register_terminator(part1_uninit);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        return init_obj.init();
    }
}