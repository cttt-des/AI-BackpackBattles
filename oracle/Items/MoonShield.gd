extends Shield

var blockAcc: int
onready var blockForMana: int = getP4()

func canAffect(item):
	return item.canBlock()

func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Block, getP3() / 100.0)
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


func canBlockDamageRes(damageRes: DamageResult) -> bool:
	return damageRes.triggerOnAttacked()
