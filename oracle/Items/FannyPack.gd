extends "res://Items/Bag.gd"

onready var speedBonus: = getP1() / 100

func onCombatStart():
	var active = false
	var totalSpeed = speedBonus
	if isTypeInInventory(ItemBook.bagtacularDescriptor):
		totalSpeed += ItemBook.bagtacularDescriptor.getP("speed") / 100.0
	
	for item in getItemsInside():
		if canApplyEffect(item):
			item.addSpeed(totalSpeed)
			active = true
	
	if active:
		activate()

func canApplyEffect(toItem):
	return toItem.hasCooldown() and not toItem.isBag()
