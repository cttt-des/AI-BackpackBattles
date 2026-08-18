extends Node2D

export var showIfDragged: = true
export var showForOpponent: = true

onready var offset = position
onready var label = $Label
onready var item = get_parent()
onready var index = 1 if name.ends_with("2") else 0

func _ready():
	hide()
	set_process(false)
	
	if (item.pooled or item.ownerType == Item.Owner.RecipeBook or 
		(item.ownerType == Item.Owner.Opponent and not showForOpponent)):
		pass
	else:
		item.connect("hovered", self, "onItemHovered")
		item.connect("unhovered", self, "onItemHoverEnd")

func onItemHovered():
	set_process(true)

func onItemHoverEnd():
	set_process(false)
	hide()

func _process(delta):




		
	var showCounter: = false

	if Game.tooltipsEnabled():
		if item.dragged:
			showCounter = showIfDragged
		else:
			showCounter = item.placed and Game.draggedItem == null
	
	visible = showCounter
	if showCounter:
		if index == 0:
			label.text = str(item.getCounterValue())
		else:
			label.text = str(item.getCounterValue2())
		
		call_deferred("positionGoldLabel")
		
func positionGoldLabel():
	global_rotation = 0
	global_position = item.global_position + offset
