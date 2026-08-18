extends Weapon

onready var removeDam: = getP("dam")
onready var bonusDam: = getP("bonusdam")

var opponentWeapons: = []

func onPrepare():
	opponentWeapons.clear()
	for item in opponent().INVENTORY.getItems():
		if item.canBeEmpowered():
			opponentWeapons.push_back(item)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		for weapon in opponentWeapons:
			weapon.purgeDamage(removeDam)
		addBonusDamage(bonusDam)
