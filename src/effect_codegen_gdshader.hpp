/*
 * Copyright (C) 2014 Patrick Mours
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <effect_codegen.hpp>

#include <memory> // std::unique_ptr
#include <algorithm> // std::find_if

namespace reshadefx
{
	/// <summary>
	/// Creates a back-end implementation for gdshader code generation.
	/// </summary>
	/// <param name="vulkan_semantics">Generate gdshader for OpenGL or for Vulkan.</param>
	/// <param name="debug_info">Whether to append debug information like line directives to the generated code.</param>
	/// <param name="uniforms_to_spec_constants">Whether to convert uniform variables to specialization constants.</param>
	/// <param name="enable_16bit_types">Use real 16-bit types for the minimum precision types "min16int", "min16uint" and "min16float".</param>
	/// <param name="flip_vert_y">Insert code to flip the Y component of the output position in vertex shaders.</param>
	codegen* create_codegen_gdshader(bool vulkan_semantics, bool debug_info, bool uniforms_to_spec_constants, bool enable_16bit_types = false, bool flip_vert_y = false);
}
