extends Item

const activationParticles = preload("res://Items/Exclusive/Particles/EchoingBattlecryActivationParticles.tscn")

var affectedItems: Array

onready var speedPerItem: = getP("speed") / 100.0

func canAffect(item):
	return item.hasStartofBattle()

func onPrepare():
	affectedItems = getAffectedItems()
	affectedItems.shuffle()
	
	addSpeed(speedPerItem * affectedItems.size())

func doCooldownEffect():
	if not affectedItems.empty():
		var item = affectedItems.pop_back()
		item.repeatCombatStart()
		var particles = ObjectPool.particleOneShot(activationParticles, get_parent())
		particles.global_position = item.global_position
		if affectedItems.empty():
			onAfterEffectFinished()
		else:
			activate()
