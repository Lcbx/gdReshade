# gdReshade : Reshade post-processing for Godot

this [extension](https://github.com/godotengine/godot-cpp) aims to import [Reshade](https://github.com/crosire/reshade) shaders natively within the [Godot Engine](https://godotengine.org/).  
It's an experiment with both postprocessing and writing an extension.


There's a demo project that shows how to use the extension.  
Please take a look at the [GDExtension issue tracker](https://github.com/Zylann/godot_voxel/issues/442) before reporting an issue.

_⚠ I do not intend to maintain this, but will review any PRs_


### TODO

* write a custom ```reshadefx::codegen``` class to generate gdshader code instead of glsl (right now you have to do the [conversion to gdshader](https://docs.godotengine.org/en/latest/tutorials/shaders/converting_glsl_to_godot_shaders.html) by hand).
* create 1 shader per pass
* create uniforms with godot attributes (```hint_range```,```hint_default```,...)
* translate correponding built-ins (ReShade::BackBuffer, BUFFER_WIDTH, ...)


