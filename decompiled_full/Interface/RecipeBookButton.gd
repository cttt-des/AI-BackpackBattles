extends FocusGrabbingButton

const anvil_hovered = preload("res://Interface/AnvilButton_hovered.png")
const anvil = preload("res://Interface/AnvilButton.png")

func _ready():
	if not Game.recipeBook:
		if Game.showExclusiveContent():
			Game.recipeBook = load("res://Items/Exclusive/RecipeBook_full.tscn").instance()
		else:
			Game.recipeBook = load("res://Interface/RecipeBook.tscn").instance()
	Game.connect("warp_cursor_shop", self, "onCursorWarp")

func onHover():
	.onHover()
	self.icon = anvil_hovered

func onHoverEnd():
	.onHoverEnd()
	self.icon = anvil

func onPressed():
	.onPressed()
	if not Game.draggedItem and not InputBlocker.isActive():
		Game.recipeBook.open()
		onHoverEnd()

func onCursorWarp():
	if is_visible_in_tree():
		Game.addPointOfInterest(rect_global_position + rect_pivot_offset)
