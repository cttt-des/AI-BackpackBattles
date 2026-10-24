extends FocusGrabbingButton

const itemLibraryScene = preload("res://Interface/ItemLibrary/ItemLibrary.tscn")
const normalTex = preload("res://Interface/ItemLibrary/ItemLibraryButton.png")
const hoveredTex = preload("res://Interface/ItemLibrary/ItemLibraryButton_hovered.png")

func _ready():
	if not Game.itemLibrary:
		Game.itemLibrary = itemLibraryScene.instance()
		Util.callNextFrame(Game.itemLibrary, "init")
	Game.connect("warp_cursor_shop", self, "onCursorWarp")

func onHover():
	.onHover()
	self.icon = hoveredTex

func onHoverEnd():
	.onHoverEnd()
	self.icon = normalTex

func onPressed():
	.onPressed()
	if not Game.draggedItem and not InputBlocker.isActive():
		Game.itemLibrary.open()
		onHoverEnd()

func onCursorWarp():
	if is_visible_in_tree():
		Game.addPointOfInterest(rect_global_position + rect_pivot_offset)
