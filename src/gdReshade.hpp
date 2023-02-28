#ifndef GDRESHADE_H
#define GDRESHADE_H

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/class_db.hpp>


namespace godot {

class Reshade : public Object {
	GDCLASS(Reshade, Object)

	private:
		
	protected:
		
		static void _bind_methods();
		
		Reshade(){}
		~Reshade(){}
		static RID compile_shader(String path, Vector2 viewport_size, bool from_source);

	public:
		
		static RID compile_shader_source(String source, Vector2 viewport_size);
		static RID compile_shader_path(String path, Vector2 viewport_size);
};

}

#endif