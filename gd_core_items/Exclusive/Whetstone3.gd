extends "res://gd_core_items/Whetstone.gd"
var blockFactor

func canAffect(item):
	return item.canBlock() or .canAffect(item)


func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Block, blockFactor)

func _readyInit():
	._readyInit()
	blockFactor = getP("blockfactor") / 100.0
