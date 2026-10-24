extends Item

func canAffect(item):
	return item.canBeEmpowered()

func onPrepare():
	character().changeBuffProtectionChance(getChance())
	character().changeResistChance(Game.EventType.Blind, getChance2())
	character().changeResistChance(Game.EventType.Cold, getChance2())

func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(getP1())
	activate()
