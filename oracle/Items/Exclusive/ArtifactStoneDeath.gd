extends "res://Items/Stone.gd"

onready var activationParticles = $Icon / ActivationParticles
var lastFatigueDam: int

func onPrepare():
	lastFatigueDam = 0
	connectForCombat(opponent(), "fatigue_damage_changed", "onFatigueDamageChanged")
	connectForCombat(Game.combatTimer, "fatigue_damage_changed", "onFatigueDamageChanged")

func canAffect(item):
	return item.canDamage()

func onFatigueDamageChanged():
	var fatigueDam = Game.fatigueDamageSource.minDamage + opponent().getBonusFatigueDamage()
	var fatigueDiff = fatigueDam - lastFatigueDam
	lastFatigueDam = fatigueDam
	
	for item in getAffectedItems():
		item.changeCritChancePercent(getChance() * fatigueDiff)

func preHit():
	inflictFatigueDamage()
	activationParticles.activate()
	
