extends "res://Interface/ItemLibrary/ItemFilterButton.gd"

onready var label = $Label
onready var iconOutline = $Outline

func onHover():
	.onHover()
	label.set("custom_colors/default_color", Util.paramColor)
	

func onHoverEnd():
	.onHoverEnd()
	label.set("custom_colors/default_color", Game.SOFTWHITE)
	

func _notification(what):
	if what == NOTIFICATION_EXIT_TREE:
		label.set("custom_colors/default_color", Game.SOFTWHITE)
		

func _ready():
	if label is RichTextLabel:
		label.formatParams = {"treasure": Util.getIcon("treasure", 30)}
		
