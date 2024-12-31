#include "heartNode.h"
#include "heartNode-type.h"
#include<gdextension_interface.h>
#include<godot_cpp/core/defs.hpp>
#include<godot_cpp/godot.hpp>

void heartNode_init(ModuleInitializationLevel p_level) {
    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE) return;
    GDREGISTER_CLASS(HeartNode);
}

void heartNode_tem(ModuleInitializationLevel p_level) {
    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE) return;
}

extern "C" {
    GDExtensionBool GDE_EXPORT heartNode_main_init(GDExtensionInterfaceGetProcAddress p_get, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_init) {
        GDExtensionBinding::InitObject init_obj(p_get, p_library, r_init);
        init_obj.register_initializer(heartNode_init);
        init_obj.register_terminator(heartNode_tem);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        return init_obj.init();
    }
}