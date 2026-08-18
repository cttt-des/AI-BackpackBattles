extends "res://Interface/Tooltips/SimpleTooltip.gd"

onready var subclassesControl = $VBoxContainer / Subclasses

func setParams(header, description):
	.setParams(header, description)
	
	var subclassItems = ItemBook.getSubclassItemDescr(Game.curClass)
	
	for i in 5:
		subclassesControl.get_child(i).setSubclass(subclassItems[i])
