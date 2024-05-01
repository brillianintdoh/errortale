#include "part2.h"
#include "part2_type.h"
#include<gdextension_interface.h>
#include<godot_cpp/core/defs.hpp>
#include<godot_cpp/godot.hpp>
using namespace godot;

void part2_init(ModuleInitializationLevel p_level) {
    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    ClassDB::register_class<Part2>();
}

void part2_uninit(ModuleInitializationLevel p_level) {
    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT part2_main_init(GDExtensionInterfaceGetProcAddress p_get, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_init) {
        GDExtensionBinding::InitObject init_obj(p_get, p_library, r_init);
        init_obj.register_initializer(part2_init);
        init_obj.register_terminator(part2_uninit);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        return init_obj.init();
    }
}