extends "res://gd_core_items/Pan.gd"

func onDealtDamage(damageRes: CoreDamageResult):
	var event = tryUseMana(getP2(), damageRes.event)
	if event:
		var affected = getAffectedItems()
		ctx.rng.shuffleEngine(affected, "Eggscalibur.gd:9")
		# ★ np24 诊断（受控）：镜像神谕 ESHUF 行，洗牌后记录受影响物品标识串，
		#   供两侧逐抽对位点名。np25棋盘面重建回植（r1_0 改道 shuffleEngine 后
		#   同位补回；builder 无此手补）。
		var _ids := ""
		for food in affected:
			_ids += String(food.descriptor.identifier) + "|"
		ctx.rng.trace_diag("ESHUF", str(_ids), "t=" + str(ctx.time), "")
		for food in affected:
			food.doCooldownEffect()
		

func _readyInit():
	._readyInit()
	pass
