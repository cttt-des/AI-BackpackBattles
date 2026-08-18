extends "res://Items/Pan.gd"

const activationParticles = preload("res://Items/Particles/EggscaliburActivationParticles.tscn")

func onDealtDamage(damageRes: DamageResult):
	var event = tryUseMana(getP2(), damageRes.event)
	if event:
		var affected = getAffectedItems()
		affected.shuffle()
		for food in affected:
			food.doCooldownEffect()
		
		ObjectPool.particleOneShot(activationParticles, sprite)
