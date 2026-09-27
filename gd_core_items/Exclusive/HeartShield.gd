extends Shield
var activated: = false
var regenGiven: int
var fillAnimation
var healamp
var blockFactor
var regenNeeded
var regenOnBlock
var regenMax

func canAffect(item):
	return (item.canBlock() or 
			item.canHealOrLifesteal() or 
			item.gainsStack(CoreConst.Stack.Regeneration))


func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Block, blockFactor)
		item.changeHealAmp(healamp)
		item.changeAmplificiationChancePercent(CoreConst.EventType.Regeneration, getChance2())
	
	setState(false)
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")
	regenGiven = 0


func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	
	if regenGiven < regenMax:
		giveRegeneration(regenOnBlock, blockedDamageRes.event)
		regenGiven += regenOnBlock
	activate()


func onRegenChanged(amount, event):
	if amount > 0 and not activated and character().getRegeneration() >= regenNeeded:
		setState(true, true)
		var event2 = useRegeneration(regenNeeded, event)
		giveMaxHealth(getP_m("maxhealth"), event2)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(filled):
	if activated == filled: return
	activated = filled
	
	if filled:
		pass
	else:
		pass



func preTakeDamage(damageRes: CoreDamageResult):
	if activated:
		if damageRes.damageSource.isAttackOrEffect() and rollChance():
			blockedDamageRes = damageRes
			beforeBlock()
	else:
		.preTakeDamage(damageRes)

func _readyInit():
	._readyInit()
	healamp = getP("healamp") / 100.0
	blockFactor = getP("block") / 100.0
	regenNeeded = int(getP("regent"))
	regenOnBlock = int(getP("regen"))
	regenMax = int(getP("max_regen"))
