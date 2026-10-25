extends Item

func canAffect(item):
	return item.getRarity() >= CoreConst.Rarity.Legendary


func onPreCombatStart():
	giveReflectStacks(getNumAffectedItems() * getP2())
	activate()


func onCombatStart():
	
	pass


func onCalcTradeChance():
	pass

func _readyInit():
	._readyInit()
	pass
