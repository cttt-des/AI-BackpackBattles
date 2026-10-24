extends Label

func _ready() -> void :
	Game.PLAYER.connect("class_changed", self, "updateText")
	Game.PLAYER.connect("stamina_regen_changed_ui", self, "updateText")
	updateText()

func updateText():
	text = "+" + String(stepify(Game.PLAYER.getStaminaRegeneration(), 0.1))
