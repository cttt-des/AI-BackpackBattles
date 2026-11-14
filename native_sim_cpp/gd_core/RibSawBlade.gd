extends Weapon
var opponentWeapons: = []
var removeDam
var bonusDam

func onPrepare():
	opponentWeapons.clear()
	for item in opponent().INVENTORY.getItems():
		if item.canBeEmpowered():
			opponentWeapons.push_back(item)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		for weapon in opponentWeapons:
			weapon.purgeDamage(removeDam)
		addBonusDamage(bonusDam)

func _readyInit():
	._readyInit()
	removeDam = getP("dam")
	bonusDam = getP("bonusdam")
