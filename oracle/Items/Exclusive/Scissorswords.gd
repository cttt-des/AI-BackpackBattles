extends "res://Items/Lightsaber.gd"

const rapierParticles = preload("res://Items/Particles/RapierActivationParticles.tscn")

onready var luckNeeded: = int(getP("luckt"))
onready var bonusDam: = getP("dam")
onready var luck: = int(getP("luck"))
onready var regen: = int(getP("regen"))

func inflict(duration, event):
	.inflict(duration, event)
	giveStacksTemporary(character(), Game.EventType.Blind, 
		blind, duration, event)

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		if character().getLucky() >= luckNeeded:
			var event = useLucky(luckNeeded, damageRes.event)
			addBonusDamage(bonusDam)
			giveRegeneration(regen, event)
			var particles = ObjectPool.particleOneShot(rapierParticles, sprite)
			particles.rotation_degrees = 180
			particles.position = Vector2( - 226, 0)
	else:
		giveLucky(luck, damageRes.event)
		var particles = ObjectPool.particleOneShot(rapierParticles, sprite)
		particles.rotation_degrees = 0
		particles.position = Vector2(284, 6)
