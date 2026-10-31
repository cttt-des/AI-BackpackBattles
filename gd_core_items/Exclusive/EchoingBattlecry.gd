extends Item
var affectedItems: Array
var speedPerItem

func canAffect(item):
	return item.hasStartofBattle()


func onPrepare():
	affectedItems = getAffectedItems()
	# ★ np25 evt105 f09 面 EBARR 探针（双门控零耗链）：EB 洗牌输入/输出序定谳
	#   ——首分歧=EB 首弹弹了不同 Piggybank（全局链 j 值 or 输入序差）。
	var _b = ""
	var _aft = ""
	if ctx.rng.oracle_trace and ctx.rng._stacktrace:
		for _a in affectedItems:
			_b += String(_a.descriptor.identifier) + "@" + str(_a.occupiedCells[0]) + ","
	ctx.rng.shuffleEngine(affectedItems, "Exclusive/EchoingBattlecry.gd:14")
	if ctx.rng.oracle_trace and ctx.rng._stacktrace:
		for _a in affectedItems:
			_aft += String(_a.descriptor.identifier) + "@" + str(_a.occupiedCells[0]) + ","
		ctx.rng.trace_diag("EBARR", "ot" + str(int(ownerType)), _b, _aft)

	addSpeed(speedPerItem * affectedItems.size())


func doCooldownEffect():
	if not affectedItems.empty():
		var item = affectedItems.pop_back()
		item.repeatCombatStart()
		if affectedItems.empty():
			onAfterEffectFinished()
		else:
			activate()

func _readyInit():
	._readyInit()
	speedPerItem = getP("speed") / 100.0
