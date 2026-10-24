extends "res://Items/Exclusive/VampiricPotion.gd"

onready var lifestealTimer = $LifestealTimer
onready var lifestealPerTrigger: = getP3() / 100.0
var curLifesteal: float
var lifestealGiven: Array

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

func onOpponentDamaged(damageRes: DamageResult):
	if curLifesteal > 0:
		if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
			heal(ceil(damageRes.damage * curLifesteal), damageRes.event)

func onLifestealTimeout():
	curLifesteal -= lifestealGiven.pop_front()

func onCombatEnd():
	lifestealTimer.stop()
