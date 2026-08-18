extends Button

export var localize = true
export var onCharacter = false

const hoverColor = Color(1, 0.890196, 0.215686)

onready var label = $Label

func _ready() -> void :
	if Game.TRAILER or Game.PLAYTEST or Game.FULLVERSION:
		hide()
	else:
		if localize:
			add_to_group("Localized")
			Util.localizeFonts(label)
			updateLocale()

func updateLocale():
	if onCharacter:
		label.text = tr("BUTTON_WishlistCharacter")
	else:
		label.text = tr("BUTTON_Wishlist")

func _pressed() -> void :
	Game.onClickButton()
	
	var res = OS.shell_open("steam://advertise/2427700")
	
	if res != OK:
		OS.shell_open("https://store.steampowered.com/app/2427700")

func onHover() -> void :
	label.set("custom_colors/font_color", hoverColor)
	Game.onHoverInteractable(self)

func onHoverEnd() -> void :
	label.set("custom_colors/font_color", Game.SOFTWHITE)
	Game.onHoverInteractableEnd(self)
