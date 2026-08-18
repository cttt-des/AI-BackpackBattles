extends Label

func _ready() -> void :
	Game.connect("character_changed", self, "updateLocale")
	Util.localizeFonts(self)
	add_to_group("Localized")
	updateLocale()

func updateLocale():
	text = Game.getClassName()
	set("custom_colors/font_color", Game.classResources[Game.curClass].color)
	
