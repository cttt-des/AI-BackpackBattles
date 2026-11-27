extends "res://gd_core_items/BoxofRiches.gd"

func onCombatStart():
	giveMaxHealth(inventory.countSocketedGems() * getP_m("maxhealth"))
	consume()


func getRelatedItems():
	return ctx.item_book.getDescriptor("Box of Riches").gatedItems

func _readyInit():
	._readyInit()
	numGems = 2

