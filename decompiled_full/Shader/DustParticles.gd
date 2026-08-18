tool
extends Particles2D

var lastMousePos: Vector2
var poolingHandle

func preset():
	pass

func _ready():
	lastMousePos = get_global_mouse_position() - global_position
	process_material.set_shader_param("mouse_position", lastMousePos)
	process_material.set_shader_param("mouse_velocity", Vector2.ZERO)

func _physics_process(delta):
	
	
	var mousePos = get_global_mouse_position() - global_position
	var mouseVelocity = (mousePos - lastMousePos)
	
	process_material.set_shader_param("mouse_position", mousePos)
	process_material.set_shader_param("mouse_velocity", mouseVelocity)
	lastMousePos = mousePos
