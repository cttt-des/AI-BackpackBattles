extends FocusGrabbingTextureButton

func _ready():
	Game.connect("character_changed", self, "updateChibiButton")
	Util.callNextFrame(self, "updateChibiButton")
	Game.connect("chibi_setting_changed", self, "updateChibiButton")

func _toggled(button_pressed):
	flip_h = button_pressed
	Game.onClickButton()
	Game.setChibiMode(button_pressed)

func updateChibiButton():
	visible = Game.getShowChibis()
	pressed = Game.getChibiMode()
