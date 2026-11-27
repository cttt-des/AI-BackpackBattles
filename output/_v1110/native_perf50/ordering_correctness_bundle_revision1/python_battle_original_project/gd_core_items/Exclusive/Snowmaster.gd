extends Item
var iceSpeed
var cold
var empower
var coldNeeded

func canAffect(item):
	return item.hasType(CoreConst.Type.Ice)


func onPrepare():
	addSpeed(getNumAffectedItems() * iceSpeed)


func doCooldownEffect():
	if opponent().getCold() >= coldNeeded:
		giveEmpower(empower)
	else:
		inflictCold(cold)
	
	cleanseRandomDebuffs(1)
	
	activate()

func _readyInit():
	._readyInit()
	iceSpeed = getP("speed") / 100.0
	cold = int(getP("cold"))
	empower = int(getP("empower"))
	coldNeeded = int(getP("coldt"))
