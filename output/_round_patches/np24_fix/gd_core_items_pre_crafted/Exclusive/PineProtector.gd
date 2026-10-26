extends "res://gd_core_items/SpikedShield.gd"
var damblockIncrease: = 0
var damblock2
var maxblock

func getDamageBlock():
	return getParamModified("damblock", getP("damblock") + damblockIncrease)


func canAffect(item):
	return item.hasType(CoreConst.Type.Food)


func onPrepare():
	.onPrepare()
	damblockIncrease = 0
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")
	
	maxSpikes = getP("maxspikes") + getP("maxspikes_food") * getNumAffectedItems()
	

func onItemActivated(event):
	if damblockIncrease < maxblock:
		damblockIncrease += min(damblock2, maxblock - damblockIncrease)
	heal()

func _readyInit():
	._readyInit()
	damblock2 = getP("damblock2")
	maxblock = getP("maxblock")
