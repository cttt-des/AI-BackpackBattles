extends "res://gd_core_items/Pan.gd"

func onDealtDamage(damageRes: CoreDamageResult):
	var event = tryUseMana(getP2(), damageRes.event)
	if event:
		var affected = getAffectedItems()
		affected.shuffle()
		var _ids := ""
		for food in affected:
			_ids += String(food.descriptor.identifier) + "|"
		ctx.rng.trace_diag("ESHUF", str(_ids), "t=" + str(ctx.time), "")
		for food in affected:
			food.doCooldownEffect()
		

func _readyInit():
	._readyInit()
	pass
