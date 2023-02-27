
#include "register_types.h"

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "gdReshade.hpp"


using namespace godot;


void initialize_gdReshade(ModuleInitializationLevel p_level) {
	if(p_level != MODULE_INITIALIZATION_LEVEL_SERVERS) return;
	ClassDB::register_abstract_class<Reshade>(); // should not instance
}

void uninitialize_gdReshade(ModuleInitializationLevel p_level) {
	if(p_level != MODULE_INITIALIZATION_LEVEL_SERVERS) return;
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gdReshade_init(const GDExtensionInterface *p_interface, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

	init_obj.register_initializer(initialize_gdReshade);
	//init_obj.register_terminator(uninitialize_gdReshade);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SERVERS);

	return init_obj.init();
}
}