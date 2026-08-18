extends HSlider
class_name BaseSlider

export var margin = 2

func _ready() -> void :
	connect("mouse_entered", self, "onHover")
	connect("mouse_exited", self, "onHoverEnd")
	set_process(false)

func onHover():
	Util.grabFocus(self)
	Game.onHoverInteractable(self)
	set_process(true)

func onHoverEnd():
	Util.releaseFocus(self)
	Game.onHoverInteractableEnd(self)
	set_process(false)
	








func _process(delta):
	if Util.isActionPressed("ui_accept", false):
		var leftBorder = rect_global_position.x + margin
		var size = (rect_size.x * rect_scale.x) - 2 * margin
		var valueRange = max_value - min_value
		var relPos = (get_global_mouse_position().x - leftBorder) / size
		var val = min_value + (valueRange * relPos)
		if value != val:
			value = val
