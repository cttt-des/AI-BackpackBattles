extends Item
const amuletColor = Color(0.266667, 0.960784, 0.667953)
var bonusChance
var numBuffs

func canAffect(item):
	return item.canModifyChance()


func onPrepare():
	for item in getAffectedItems():
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

