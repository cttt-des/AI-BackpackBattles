extends "res://Items/Whetstone.gd"

onready var blockFactor = getP("blockfactor") / 100.0

func canAffect(item):
	return item.canBlock() or .canAffect(item)

func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Block, blockFactor)
