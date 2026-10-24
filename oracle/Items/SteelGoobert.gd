extends Goobert

var affectedWeapons = []

func canAffect_secondary(item):
	return item.canBeEmpowered()

func onPrepare():
	for item in getAffectedItems(Affected.Secondary):
		affectedWeapons.push_back(item)

func doCooldownEffect():
	for item in affectedWeapons:
		item.addBonusDamage(getP2())
	giveBlock()

func onCombatEnd():
	affectedWeapons.clear()
