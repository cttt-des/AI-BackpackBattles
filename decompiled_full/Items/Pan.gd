extends Weapon

var bonusDamage: int

func canAffect(item):
	return item.hasType(Type.Food)

func onPreCombatStart():
	addBonusDamage(getP1() * getNumAffectedItems())
