extends "res://Items/SpikedShield.gd"

onready var damblock2: = getP("damblock2")
onready var maxblock: = getP("maxblock")
var damblockIncrease: = 0

func getDamageBlock():
	return getParamModified("damblock", getP("damblock") + damblockIncrease)

func canAffect(item):
	return item.hasType(Type.Food)

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
