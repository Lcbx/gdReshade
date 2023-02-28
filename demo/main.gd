extends Node3D

func _ready():
	print(Reshade.compile_shader("test", Vector2.ZERO))

	var code : String = FileAccess.open("res://xhair.fx", FileAccess.READ).get_as_text()
	print(Reshade.compile_shader(code, get_viewport().size))
