extends Bag
var mana

func canApplyEffect(toItem):
	return toItem.gainsStack(CoreConst.Stack.Mana)


func onPrepare():
	for item in getAffectedItemsInside():
		item.changeAmplificiationChancePercent(CoreConst.EventType.Mana, getChance())
	
	character().changeProtectionChance(CoreConst.EventType.Mana, getChance2())


func onCombatStart():
	giveMana(mana)
	activate()

func _readyInit():
	._readyInit()
	mana = int(getP("mana"))
