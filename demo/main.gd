extends Node3D

func _ready():
	compileShaderTest()


func compileShaderTest():

	var v_size = get_viewport().size
	#print("viewport ", v_size)

	print(Reshade.compile_shader_source("test", v_size))

	var shaderCode : String = Reshade.compile_shader_path("res://assets/xhair.fx", v_size)
	#print(shaderCode)

	# main.gdshader is based on the generated shaderCode

	# TODO : make the translation from glsl more automatic

	var mat = $MeshInstance3D.get_active_material(0)
	mat.set_shader_parameter("V_ReShade_BackBuffer", get_viewport().get_texture())
	#$MeshInstance3D.material_override = mat
	#print(ResourceSaver.save(shader))

	await(get_tree().create_timer(5).timeout)
	get_tree().quit()


