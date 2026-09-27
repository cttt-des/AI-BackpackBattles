extends Item
var heatThreshold
var heat

func onChargeReceived(_charge):
	if character().getHeat() < heatThreshold:
		giveHeat(heat)
		miniActivate()
	else:
		pass
	


































func _readyInit():
	._readyInit()
	heatThreshold = int(getP("heatt"))
	heat = int(getP("heat"))
