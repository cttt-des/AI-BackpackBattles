extends Weapon

func canAffect(item):
	return item.hasType(Type.Magic)

func onPrepare():
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")
	connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")

func onCombatStart():
	var numAffected = getNumAffectedItems()
	if numAffected > 0:
		giveHeat(getP2() * numAffected)
		giveLucky(getP3() * numAffected)

func onHeatChanged(amount, _event):
	changeVaryingDamage(getP1() * amount)

func onLuckyChanged(amount, event):
	character().changeDebuffResistChances(getChance() * amount)
