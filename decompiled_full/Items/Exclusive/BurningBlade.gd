extends "res://Items/Exclusive/BurningSword.gd"

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		giveHeat(heatOnHit)
