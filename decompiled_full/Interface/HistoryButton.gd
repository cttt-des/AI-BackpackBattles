extends FocusGrabbingButton

onready var icon_normal = icon
const icon_hovered = preload("res://Interface/HistoryButton_hovered.png")

func _ready():
	if Game.buildHistoryDB != null:
		Game.buildHistory = load("res://Interface/BuildHistory/BuildHistory.tscn").instance()
	else:
		queue_free()

func onHover():
	.onHover()
	self.icon = icon_hovered

func onHoverEnd():
	.onHoverEnd()
	self.icon = icon_normal

func onPressed():
	.onPressed()
	if not Game.draggedItem:
		Game.buildHistory.open()
		onHoverEnd()
