# gdReshade : Reshade extension for Godot

this [extension](https://github.com/godotengine/godot-cpp)'s mission is to import [Reshade](https://github.com/crosire/reshade) shaders natively within the [Godot Engine](https://godotengine.org/)
It's an experiment with both postprocessing and writing an extension.

Biggest TODO: write a custom ```reshadefx::codegen``` class to generate gdshader code instead of glsl (right now you have to do the [conversion to gdshader](https://docs.godotengine.org/en/latest/tutorials/shaders/converting_glsl_to_godot_shaders.html) by hand).

There's a demo project that shows how to use the extension.
Please take a look at the [GDextension issue tracker](https://github.com/Zylann/godot_voxel/issues/442) before reporting an issue.

⚠ _I do not intend to maintain this, but will review any PRs_


## License

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org/>
