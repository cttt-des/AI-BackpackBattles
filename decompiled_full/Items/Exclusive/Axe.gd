extends Weapon

onready var permDamBonus: = int(getP1())

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		addBonusDamage(permDamBonus)
