extends Shield

onready var blockFactor = getP3() / 100.0

func canAffect(item):
	return item.canBlock()

func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Block, blockFactor)

func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	activate()
	
