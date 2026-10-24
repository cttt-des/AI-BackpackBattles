extends Label

func _ready():
	Game.connect("trophies_changed", self, "updateValue")
	updateValue()

func updateValue():
	text = String(Game.getTrophies())
