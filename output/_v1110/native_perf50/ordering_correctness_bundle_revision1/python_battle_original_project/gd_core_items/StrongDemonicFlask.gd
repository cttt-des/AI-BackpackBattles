extends Potion
var healingReductionTimer
var healingDebuff
var damPerDebuff
var playerHealthThreshold
var opponentHealthThreshold

func canDamage() -> bool:
	return true


func onTriggerPotion(triggerEvent = null):
	opponent().reduceHealingEfficiency(healingDebuff)
	var dam = opponent().getDebuffStacks() * damPerDebuff
	dam = ceil(dam)
	stealLife(dam, getP_m("lifesteal") / 100.0, triggerEvent)
	healingReductionTimer.start(getP_m("dur"))


func onPrepare():
	connectForCombat(character(), "character_damaged", "onPlayerDamaged")
	connectForCombat(opponent(), "character_damaged", "onOpponentDamaged")


func onPlayerDamaged(healthChange, event):
	if isEmpty(): return
	if character().getRelativeHealth() < playerHealthThreshold:
		drinkStrongDemonicFlask(event)


func onOpponentDamaged(healthChange, event):
	if isEmpty(): return
	if opponent().getRelativeHealth() < opponentHealthThreshold:
		drinkStrongDemonicFlask(event)
		

func drinkStrongDemonicFlask(event):
	# ★ np25 evt12 面 AFFL 探针（双门控零耗链）：SDF 喝毒的 affected[0] 链定谳
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


func healingReductionTimeout():
	opponent().addHealingEfficiency(healingDebuff)


func onCombatEnd():
	healingReductionTimer.stop()

func _readyInit():
	._readyInit()
	healingReductionTimer = newItemTimer("HealingReductionTimer", "healingReductionTimeout", true)
	healingDebuff = getP3() / 100.0
	damPerDebuff = getP("dam")
	playerHealthThreshold = getP("ownhpt") / 100.0 - 0.0001
	opponentHealthThreshold = getP("opphpt") / 100.0 - 0.0001
