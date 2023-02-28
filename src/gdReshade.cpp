
#include "gdNameof.hpp"
#include "gdReshade.hpp"

#include<godot_cpp/variant/utility_functions.hpp>
#include<godot_cpp/classes/os.hpp>

#include <effect_parser.hpp>
#include <effect_codegen.hpp>
#include <effect_preprocessor.hpp>
//#include <version.h> missing

#define PRINT(...) UtilityFunctions::print(__VA_ARGS__)

using namespace godot;

RID Reshade::compile_shader_source(String source, Vector2 viewport_size) {
	if (source[source.length() - 1] != '\n') {
		UtilityFunctions::push_warning("Reshade::preprocessor: script should end with an endline (\\n). adding one.");
		source = source + "\n";
	}

	//PRINT(source.utf8().get_data());
	return compile_shader(source, viewport_size, true);
}

RID Reshade::compile_shader_path(String path, Vector2 viewport_size) {
	//PRINT(path.utf8().get_data());
	return compile_shader(path.replace("res://", ""), viewport_size, false);
}

RID Reshade::compile_shader(String shader, Vector2 viewport_size, bool from_source) {

	auto shader_c_str = shader.utf8().get_data();

	reshadefx::parser parser;
	reshadefx::preprocessor pp;

	// based on command 'git describe --tags' in reshade folder => v5.7.0-2-g38cf982a
	// TODO? : automagically update this. Why doesn't Reshade just track the version.h file ?  
	pp.add_macro_definition("__RESHADE__", std::to_string(5 * 10000 + 7 * 100 + 0));
	pp.add_macro_definition("__RESHADE_PERFORMANCE_MODE__", "0");

	pp.add_macro_definition("BUFFER_WIDTH",  std::to_string(viewport_size.x));
	pp.add_macro_definition("BUFFER_HEIGHT", std::to_string(viewport_size.y));
	pp.add_macro_definition("BUFFER_RCP_WIDTH", "(1.0 / BUFFER_WIDTH)");
	pp.add_macro_definition("BUFFER_RCP_HEIGHT", "(1.0 / BUFFER_HEIGHT)");

	if (from_source)
		pp.append_string(std::string(shader_c_str), std::filesystem::path());
	else if(std::filesystem::exists(shader_c_str))
		pp.append_file(shader_c_str);
	
	else UtilityFunctions::push_error("Reshade::preprocessor: no script at given path ", shader_c_str);

	auto pp_output = pp.output();
	auto pp_errors = pp.errors();

	if (!pp_errors.empty())		UtilityFunctions::push_error("Reshade::preprocessor: ", pp_errors.c_str());
	else if (pp_output.empty()) UtilityFunctions::push_error("Reshade::preprocessor: something went wrong quietly");

	#PRINT("PP_OUTPUT\n", pp_output.c_str(), " for ", shader);

	std::unique_ptr<reshadefx::codegen> backend;
	//backend.reset(reshadefx::create_codegen_glsl(true, true, true, false));
	//backend.reset(reshadefx::create_codegen_glsl(vulkan_semantics, debug_info, spec_constants, invert_y_axis));
	//backend.reset(reshadefx::create_codegen_hlsl(shader_model, debug_info, spec_constants));
	backend.reset(reshadefx::create_codegen_hlsl(50, true, true));
	//backend.reset(reshadefx::create_codegen_spirv(vulkan_semantics, debug_info, spec_constants, invert_y_axis));

	if (!parser.parse(pp_output, backend.get()))
	{
		auto parser_errors = parser.errors();
		if (!parser_errors.empty()) UtilityFunctions::push_error("Reshade::parser: ", parser_errors.c_str());

		return *new RID;
	}
	else {
		reshadefx::module module;
		backend->write_result(module);
		//PRINT(module.hlsl.c_str());
	}


	return *new RID;
}

void Reshade::_bind_methods(){
	ClassDB::bind_static_method(CLASS_NAME, METHOD_DEF(compile_shader_source, "source", "viewport_size"), &Reshade::compile_shader_source);
	ClassDB::bind_static_method(CLASS_NAME, METHOD_DEF(compile_shader_path, "path", "viewport_size"), &Reshade::compile_shader_path);
}