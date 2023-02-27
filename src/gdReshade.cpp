#include "gdReshade.hpp"
#include "effect_parser.hpp"
#include "effect_codegen.hpp"

using namespace godot;

RID Reshade::compile_shader(String source) {
	return *new RID;
}