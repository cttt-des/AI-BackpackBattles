extends "res://gd_core_items/PestilenceFlask.gd"
var poisonTimer

func getAffectedItems(color = CoreConst.Affected.Primary) -> Array:
	# ★ np25 evt12 面 GRD 探针（双门控零耗）：aff 格级真值——faceDirection/
	#   collision 全局格/cache 格/命中物品，定 getAffectedItems 错位。
	var _r = .getAffectedItems(color)
	if ctx != null and ctx.rng != null:
		var _cp = getCollisionPoints()
		var _rc = getCellsForGlobalPositions(_cp)
		var _cc = getAffectedCellsInInventory_cached(color)
		var _names = ""
		for _a in _r:
			_names += String(_a.descriptor.identifier) + "@" + str(_a.occupiedCells) + ","
		ctx.rng.trace_diag("GRD", String(descriptor.identifier),
				"fd=" + str(faceDirection) + " cp=" + str(_cp) + " aff=" + str(_cc), _names + "n=" + str(_r.size()))
	return _r

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	poisonTimer.start(getP3())


func poisonTimerTimeout():
	inflictPoison(getP4())


func onCombatEnd():
	poisonTimer.stop()

func _readyInit():
	._readyInit()
	poisonTimer = newItemTimer("PoisonTimer", "poisonTimerTimeout", true)
