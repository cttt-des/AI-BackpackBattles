extends Item
var numActivations: int
var speedBonus
var maxActivations

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	numActivations = 0


func doCooldownEffect():
	if numActivations < maxActivations:
		for item in getAffectedItems():
			
			item.addSpeed(speedBonus)
			
		numActivations += 1
	
	if opponent().getLucky() > 0:
		removeLucky(getP3())
	
	activate()

func _readyInit():
	._readyInit()
	speedBonus = getP("speed") / 100.0
	maxActivations = int(getP("max"))
