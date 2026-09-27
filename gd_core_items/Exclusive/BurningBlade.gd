extends "res://gd_core_items/Exclusive/BurningSword.gd"

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		giveHeat(heatOnHit)

func _readyInit():
	._readyInit()
	pass
