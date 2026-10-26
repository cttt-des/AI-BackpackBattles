extends Weapon
var critBonusActive = false
var poisonThreshold: int
var activationParticles

func canAffect(item):
	return item.gainsStack(CoreConst.Stack.Poison)


func onPrepare():
	setState(false)
	connectForCombat(opponent(), "character_poison_changed", "onOpponentPoisonChanged")
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Poison, 1)


func onOpponentPoisonChanged(_amount, _event):
	var curPoison = opponent().getPoison()
	
	if not critBonusActive and curPoison >= poisonThreshold:
		setState(true)
		changeCritChancePercent(getChance())
	

func onShopEntered():
	onStateChanged(false)


func onStateChanged(_critBonusActive):
	if _critBonusActive:
		pass
	else:
		pass
	critBonusActive = _critBonusActive

func _readyInit():
	._readyInit()
	poisonThreshold = getP1()
