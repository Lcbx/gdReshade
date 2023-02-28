#ifndef GDRESHADE_H
#define GDRESHADE_H

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/Shader.hpp>


namespace godot {

class Reshade : public Object {
	GDCLASS(Reshade, Object)

	private:
		
	protected:
		
		static void _bind_methods();
		
		Reshade(){}
		~Reshade(){}

	public:

		// NOTE : use Vector2i, not Vector2, or you get Vector2.ZERO
		static String compile_shader(String shader, Vector2i viewport_size, bool from_source);
		static String compile_shader_source(String source, Vector2i viewport_size);
		static String compile_shader_path(String path, Vector2i viewport_size);
};

}

#endif