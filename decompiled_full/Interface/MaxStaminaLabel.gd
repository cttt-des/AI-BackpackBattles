extends Label

func _ready() -> void :
	Game.PLAYER.connect("class_changed", self, "updateText")
	Game.PLAYER.connect("max_stamina_changed_ui", self, "updateText")
	updateText()

func updateText():
	text = String(Game.PLAYER.getMaxStamina())
