extends ColorRect

onready var UI = get_parent()

func _unhandled_input(event: InputEvent) -> void :
	if (visible and 
		UI.visible and 
		not (event is InputEventMouseButton and event.button_index == BUTTON_LEFT) and 
		not (event is InputEventMouseMotion) and 
		not event is InputEventKey):
		
		get_tree().set_input_as_handled()
