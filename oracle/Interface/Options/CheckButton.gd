extends FocusGrabbingControl

func _toggled(button_pressed: bool) -> void :
	Settings.setValStr(name, button_pressed)

func initialize():
	set("pressed", Settings.getValStr(name))

func _ready() -> void :
	call_deferred("initialize")

func onHover():
	.onHover()
	set("custom_colors/font_color_pressed", Util.paramColor)

func onHoverEnd():
	.onHoverEnd()
	set("custom_colors/font_color_pressed", Game.SOFTWHITE)
