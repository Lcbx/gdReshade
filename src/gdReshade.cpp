
#include "gdNameof.hpp"
#include "gdReshade.hpp"
#include "effect_parser.hpp"
#include "effect_codegen.hpp"

using namespace godot;

RID Reshade::compile_shader(String source) {
	reshadefx::parser parser;
	reshadefx::preprocessor pp;
	pp.add_macro_definition("__RESHADE__", std::to_string(VERSION_MAJOR * 10000 + VERSION_MINOR * 100 + VERSION_REVISION));
	pp.add_macro_definition("__RESHADE_PERFORMANCE_MODE__", "0");
	return *new RID;
}

void Reshade::_bind_methods(){
	ClassDB::bind_static_method(CLASS_NAME, METHOD_DEF(compile_shader, "source"), &Reshade::compile_shader);
}