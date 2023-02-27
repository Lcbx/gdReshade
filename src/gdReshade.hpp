#ifndef GDRESHADE_H
#define GDRESHADE_H

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {


	class Reshade : public Object {
		GDCLASS(Reshade, Object)

		private:
			
		protected:
			
			static void _bind_methods(){
				ClassDB::bind_static_method("Reshade", D_METHOD("compile_shader", "source"), &Reshade::compile_shader);
			}
			
			Reshade(){}
			~Reshade(){}

		public:
			
			static RID compile_shader(String source);
	};

}

#endif