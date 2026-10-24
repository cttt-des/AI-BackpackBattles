extends "res://Items/BoxofRiches.gd"

func _ready():
	numGems = 2

func onCombatStart():
	giveMaxHealth(inventory.countSocketedGems() * getP_m("maxhealth"))
	consume()

func getRelatedItems():
	return ItemBook.boxOfRichesDescriptor.gatedItems
