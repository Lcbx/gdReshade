
#include "gdNameof.hpp"
#include "gdReshade.hpp"
#include "effect_codegen_gdshader.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/file_access.hpp>
//#include <godot_cpp/classes/packed_data_container.hpp>
//#include <godot_cpp/classes/rendering_server.hpp>
//#include <godot_cpp/classes/resource_saver.hpp>


#include <effect_parser.hpp>
#include <effect_preprocessor.hpp>
#include <effect_module.hpp>
#include <version.h>

#define PRINT(...) UtilityFunctions::print(__VA_ARGS__)

using namespace godot;

const char RESHADE_EXPECTED_EOL = '\n';

String Reshade::compile_shader_source(String source, Vector2i viewport_size) {
	if (source[source.length() - 1] != RESHADE_EXPECTED_EOL) {
		UtilityFunctions::push_warning("Reshade::preprocessor: script should end with an endline (\\n). adding one.");
		source = source + RESHADE_EXPECTED_EOL;
	}
	return compile_shader(source, viewport_size, true);
}

String Reshade::compile_shader_path(String path, Vector2i viewport_size) {
	// simplest way to get gogot paths ?
	auto file = FileAccess::open(path, FileAccess::ModeFlags::READ);
	path = file->get_path_absolute();
	return compile_shader(path, viewport_size, false);
}

String Reshade::compile_shader(String shader, Vector2i viewport_size, bool from_source) {

	//PRINT(shader);

	reshadefx::parser parser;
	reshadefx::preprocessor pp;

	// we generate reshade's version.h ourselves (see get_reshade_version.sh) based on the command 'git describe --tags'
	auto sVersionNumbers = String(RESHADE_VERSION).split(".", false);
	int vMajor = sVersionNumbers[0].replace("v", "").to_int();
	int vMinor = sVersionNumbers[1].to_int();

	//PRINT(RESHADE_VERSION);
	pp.add_macro_definition("__RESHADE__", std::to_string(vMajor * 10000 + vMinor * 100 + 0));
	pp.add_macro_definition("__RESHADE_PERFORMANCE_MODE__", "1");

	pp.add_macro_definition("BUFFER_WIDTH",  std::to_string(viewport_size.x));
	pp.add_macro_definition("BUFFER_HEIGHT", std::to_string(viewport_size.y));
	pp.add_macro_definition("BUFFER_RCP_WIDTH", "(1.0 / BUFFER_WIDTH)");
	pp.add_macro_definition("BUFFER_RCP_HEIGHT", "(1.0 / BUFFER_HEIGHT)");

	auto shader_std_str = std::string(shader.utf8().get_data());
	if (from_source) {
		pp.append_string(shader_std_str, std::filesystem::path());
	}
	else if (FileAccess::file_exists(shader)) {
		pp.append_file(shader_std_str);
		PRINT(shader_std_str.c_str());
	}
	// not from source and can't find the source file 
	else {
		UtilityFunctions::push_error("Reshade::preprocessor: no script at given path <", shader_std_str.c_str(), ">");
		return "";
	}

	auto pp_output = pp.output();
	auto pp_errors = pp.errors();

	if (!pp_errors.empty())		UtilityFunctions::push_error("Reshade::preprocessor: ", pp_errors.c_str());
	else if (pp_output.empty()) UtilityFunctions::push_error("Reshade::preprocessor: something went wrong quietly");
	
	std::unique_ptr<reshadefx::codegen> backend;
	//			  reshadefx::create_codegen_glsl(vulkan_semantics, debug_info, spec_constants, invert_y_axis));
	backend.reset(reshadefx::create_codegen_gdshader(true, false, false, false));

	if (!parser.parse(pp_output, backend.get()))
	{
		auto parser_errors = parser.errors();
		if (!parser_errors.empty()) UtilityFunctions::push_error("Reshade::parser: ", parser_errors.c_str());
		else						UtilityFunctions::push_error("Reshade::parser: something went wrong quietly");
		return "";
	}

	reshadefx::module module;
	backend->write_result(module);

	//PRINT(module.hlsl.c_str());

	// reshade uses hlsl property for glsl...
	String glslSource = String(module.hlsl.c_str());

	//for (auto entry : module.entry_points) {
	//	//PRINT(entry.name.c_str(), " ", (int)entry.type);
	//	auto shaderType = entry.type == reshadefx::shader_type::vs ? "vertex" : (entry.type == reshadefx::shader_type::ps ? "fragment" : "compute_shader");
	//	glslSource = glslSource.replace(entry.name.c_str(), shaderType);
	//}

	return glslSource;
}

void Reshade::_bind_methods(){
	ClassDB::bind_static_method(CLASS_NAME, FAST_BIND(compile_shader_source, "source", "viewport_size"), &Reshade::compile_shader_source);
	ClassDB::bind_static_method(CLASS_NAME, FAST_BIND(compile_shader_path,	 "path",   "viewport_size"), &Reshade::compile_shader_path);
}