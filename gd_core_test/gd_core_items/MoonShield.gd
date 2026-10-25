extends Shield
var blockAcc: int
var blockForMana: int

func canAffect(item):
	return item.canBlock()


func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Block, getP3() / 100.0)
		connectForCombat(item, "gave_block", "onItemGaveBlock")
	blockAcc = 0
	

func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	activate()
	

func onItemGaveBlock(amount, event):
	blockAcc += amount
	var mana = blockAcc / blockForMana
	blockAcc %= blockForMana
	if mana > 0:
		giveMana(mana, event)
		miniActivate()



func canBlockDamageRes(damageRes: CoreDamageResult) -> bool:
	return damageRes.triggerOnAttacked()

func _readyInit():
	._readyInit()
	blockForMana = getP4()
