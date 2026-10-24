extends FocusGrabbingTextureButton

onready var buttonLabel = get_parent().get_node("%WardrobeLabel")

func _ready():
	if not Game.wardrobe:
		Game.wardrobe = load("res://Interface/Wardrobe/Wardrobe.tscn").instance()
		Game.wardrobe.connect("closed", self, "onWardrobeClosed")

func onPressed():
	.onPressed()
	if not Game.draggedItem:
		if Game.wardrobe.is_inside_tree():
			Game.wardrobe.close()
			
		elif not Game.wardrobe.isOpen:
			Game.wardrobe.open()
			buttonLabel.translationKey = "BUTTON_CloseWardrobe"
			buttonLabel.updateText()

func onWardrobeClosed():
	buttonLabel.translationKey = "BUTTON_OpenWardrobe"
	buttonLabel.updateText()
