extends FocusGrabbingControl

export (Texture) var iconHovered
onready var iconUnchecked = get("custom_icons/radio_unchecked")

func _ready():
	connect("toggled", self, "_toggled")

func onHover():
	.onHover()
	if not self.pressed:
		set("custom_icons/radio_unchecked", iconHovered)
	set("custom_colors/font_color_pressed", Util.paramColor)

func onHoverEnd():
	.onHoverEnd()
	if not self.pressed:
		setUnchecked()
	set("custom_colors/font_color_pressed", Game.SOFTWHITE)

func _toggled(button_pressed):
	if not button_pressed:
		setUnchecked()

func setPressed(isPressed):
	me.set_pressed_no_signal(isPressed)
	if not isPressed:
		setUnchecked()

func setUnchecked():
	set("custom_icons/radio_unchecked", iconUnchecked)
