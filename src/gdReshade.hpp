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

		// NOTE : use Vector2i, not Vector2, or you get Vector2.ZERO
		static inline String compile_shader(String shader, Vector2i viewport_size, bool from_source = false, bool glsl = false);

	public:

		static String compile_gdshader_source(String source, Vector2i viewport_size);
		static String compile_gdshader_path(String path, Vector2i viewport_size);

		// for compute shaders
		static String compile_glsl_source(String source, Vector2i viewport_size);
		static String compile_glsl_path(String path, Vector2i viewport_size);
};

}

#endif