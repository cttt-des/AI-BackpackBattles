extends Node2D

func _ready():
	Util.localizeFonts(self)
	add_to_group("Localized")
	updateLocale()

func _process(delta: float) -> void :
	checkState()
	if visible:
		global_position = get_global_mouse_position()

func checkState():
	if Game.getTotalRotations() > 0:
		queue_free()
	else:
		visible = (Game.draggedItem != null)

func updateLocale():
	if Game.usingController:
		var text = tr("HINT_Rotate_CONTROLLER")
		var icon1 = ControllerIcons.getIconFromAction("rotate_left_button_controller")
		var icon2 = ControllerIcons.getIconFromAction("rotate_right_button_controller")
		text = text.format({
			"button1": Util.imageToBbcode(icon1, 60), 
			"button2": Util.imageToBbcode(icon2, 60)})
		$Hint.bbcode_text = "[center]" + text
	else:
		$Hint.bbcode_text = "[center]" + tr("HINT_Rotate")
