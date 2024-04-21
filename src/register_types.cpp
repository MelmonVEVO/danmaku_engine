#include "register_types.h"

#include "bulletpool.h"
#include "emitter2d.h"
#include "bulletsettings.h"
#include "bulletpattern.h"
#include "pointpattern.h"
#include "ringpattern.h"
#include "arcpattern.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;


void initialise_danmaku_engine(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<BulletSettings>();
    ClassDB::register_class<BulletPattern>();
    ClassDB::register_class<PointPattern>();
    ClassDB::register_class<RingPattern>();
    ClassDB::register_class<ArcPattern>();

    ClassDB::register_class<BulletPool>();
    ClassDB::register_class<Emitter2D>();
}


void uninitialise_danmaku_engine(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
GDExtensionBool GDE_EXPORT danmaku_engine_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialise_danmaku_engine);
	init_obj.register_terminator(uninitialise_danmaku_engine);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}