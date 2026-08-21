extends Control

var viewer

func _gui_input(event):
	if not is_instance_valid(viewer):
		return
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		viewer.close_from_click_outside()
		accept_event()
