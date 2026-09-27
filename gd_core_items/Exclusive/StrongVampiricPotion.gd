extends "res://gd_core_items/Exclusive/VampiricPotion.gd"
var curLifesteal: float
var lifestealGiven: Array
var lifestealTimer
var lifestealPerTrigger

func onPrepare():
	.onPrepare()
	curLifesteal = 0.0
	lifestealGiven.clear()
	connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")


func onTriggerPotion(triggerEvent = null):
	
	var amount = getP_m("lifesteal") / 100.0
	curLifesteal += amount
	lifestealGiven.push_back(amount)
	lifestealTimer.start(getP_m("dur"))
	giveVampirism(getP2(), triggerEvent)


func onOpponentDamaged(damageRes: CoreDamageResult):
	if curLifesteal > 0:
		if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
			heal(ceil(damageRes.damage * curLifesteal), damageRes.event)


func onLifestealTimeout():
	curLifesteal -= lifestealGiven.pop_front()


func onCombatEnd():
	lifestealTimer.stop()

func _readyInit():
	._readyInit()
	lifestealTimer = newItemTimer("LifestealTimer", "onLifestealTimeout", true)
	lifestealPerTrigger = getP3() / 100.0
