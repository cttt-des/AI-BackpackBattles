extends Weapon
var bonusDamage: int

func canAffect(item):
	return item.hasType(CoreConst.Type.Food)


func onPreCombatStart():
	addBonusDamage(getP1() * getNumAffectedItems())

func _readyInit():
	._readyInit()
	pass
