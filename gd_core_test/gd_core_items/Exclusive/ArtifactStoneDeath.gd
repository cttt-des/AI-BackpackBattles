extends "res://gd_core_items/Stone.gd"
var lastFatigueDam: int
var activationParticles

func onPrepare():
	lastFatigueDam = 0
	connectForCombat(opponent(), "fatigue_damage_changed", "onFatigueDamageChanged")
	connectForCombat(ctx.combat, "fatigue_damage_changed", "onFatigueDamageChanged")


func canAffect(item):
	return item.canDamage()


func onFatigueDamageChanged():
	var fatigueDam = ctx.fatigueDamageSource.minDamage + opponent().getBonusFatigueDamage()
	var fatigueDiff = fatigueDam - lastFatigueDam
	lastFatigueDam = fatigueDam
	
	for item in getAffectedItems():
		item.changeCritChancePercent(getChance() * fatigueDiff)


func preHit():
	inflictFatigueDamage()
	

func _readyInit():
	._readyInit()
	pass
