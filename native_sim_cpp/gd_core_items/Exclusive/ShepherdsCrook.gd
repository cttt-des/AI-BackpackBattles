extends Item

func canAffect(item):
	return item.canBeEmpowered()


func onPrepare():
	character().changeBuffProtectionChance(getChance())
	character().changeResistChance(CoreConst.EventType.Blind, getChance2())
	character().changeResistChance(CoreConst.EventType.Cold, getChance2())


func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(getP1())
	activate()

func _readyInit():
	._readyInit()
	pass
