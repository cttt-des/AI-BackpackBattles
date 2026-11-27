extends Potion

func onTriggerPotion(triggerEvent = null):
	inflictPoison(getP1(), triggerEvent)
	selfInflictPoison(getP2(), triggerEvent)


func onPrepare():
	connectForCombat(opponent(), "character_healed", "onOpponentHeal")


func onOpponentHeal(_amount, event):
	if isEmpty(): return

	# ★ np25 evt12 面 AFFL 探针（双门控零耗链）：反制投掷链定谳——
	#   getAffectedItems 运行时值（gd 3 投 v oracle 2 投，affected[0] 链
	#   是否多执行一级）。定谳后可移除或保留（零耗不影响行为）。
	var _aff = getAffectedItems()
	var _aff_names = ""
	for _a in _aff:
		_aff_names += String(_a.descriptor.identifier) + ","
	ctx.rng.trace_diag("AFFL", String(descriptor.identifier), "n=" + str(_aff.size()), _aff_names)

	drink()

	triggerPotion(event)

	var affected = getAffectedItems()
	if not affected.empty():
		affected[0].triggerPotion(event)
		affected[0].miniActivate()

	activate()

func _readyInit():
	._readyInit()
	pass
