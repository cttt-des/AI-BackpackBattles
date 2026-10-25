extends "res://gd_core_items/Pan.gd"

func onDealtDamage(damageRes: CoreDamageResult):
	var event = tryUseMana(getP2(), damageRes.event)
	if event:
		var affected = getAffectedItems()
		affected.shuffle()
		for food in affected:
			food.doCooldownEffect()
		

func _readyInit():
	._readyInit()
	pass
