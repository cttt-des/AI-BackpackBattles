extends Item
const amuletColor = Color(0.266667, 0.960784, 0.667953)
var bonusChance
var numBuffs

func canAffect(item):
	return item.canModifyChance()


func onPrepare():
	var _aff = getAffectedItems()
	# ★ np51㊳终⑪ 增伤面探针（GD_FORTPROBE 门控，零 rng 消耗）
	if OS.get_environment("GD_FORTPROBE") != "":
		var _names := ""
		for _a in _aff:
			_names += String(_a.descriptor.identifier) + ","
		print("[FORT] t=prepare bonusChance=", bonusChance, " affected=", _names,
				" mult=", bonusChancePercent_mult)
	for item in _aff:
		item.addBonusChance(bonusChance)


func doCooldownEffect():
	giveMostBuffs(numBuffs)
	onAfterEffectFinished()


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 5

func _readyInit():
	._readyInit()
	bonusChance = getP("chance")
	numBuffs = int(getP("buffs"))
	pass

