extends Control

const maxSize = Vector2(200, 120)

onready var label = $Label
onready var itemNode = $Node2D

var item = null

func setSubclass(descriptor):
	if item != null:
		item.discard()
	
	label.text = Game.getTranslatedSubclassName(descriptor.startsSubclass)
	item = ItemBook.instantiateItem_pooled(descriptor)
	item.ownerType = item.Owner.Tooltip
	itemNode.add_child(item)
	item.initTooltip()
	item.scaleToFit(maxSize, 0.8)
	item.position = item.getSpriteOffset()
