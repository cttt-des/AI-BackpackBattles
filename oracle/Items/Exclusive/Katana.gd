extends "res://Items/RibSawBlade.gd"

const activationParticles = preload("res://Items/Particles/KatanaActivationParticles.tscn")

onready var buffsNeeded: = int(getP("buffst"))
onready var removeBuffs: = int(getP("buffs"))

func onPreDealDamage_early(damageRes: DamageResult):
	.onPreDealDamage_early(damageRes)
	if damageRes.hasHit():
		var buffs = opponent().getBuffStacks()
		if buffs >= buffsNeeded:
			removeMostBuffs(removeBuffs)
			ObjectPool.particleOneShot(activationParticles, sprite)
