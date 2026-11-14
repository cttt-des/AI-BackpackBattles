extends Shield
var blockFactor

func canAffect(item):
	return item.canBlock()


func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Block, blockFactor)


func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	activate()
	

func _readyInit():
	._readyInit()
	blockFactor = getP3() / 100.0
