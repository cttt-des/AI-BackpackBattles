extends Item
var affectedItems: Array
var speedPerItem

func canAffect(item):
	return item.hasStartofBattle()


func onPrepare():
	affectedItems = getAffectedItems()
	affectedItems.shuffle()
	
	addSpeed(speedPerItem * affectedItems.size())


func doCooldownEffect():
	if not affectedItems.empty():
		var item = affectedItems.pop_back()
		item.repeatCombatStart()
		if affectedItems.empty():
			onAfterEffectFinished()
		else:
			activate()

func _readyInit():
	._readyInit()
	speedPerItem = getP("speed") / 100.0
