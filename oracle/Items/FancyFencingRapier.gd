extends Weapon

const activationParticles = preload("res://Items/Particles/RapierActivationParticles.tscn")

onready var luckNeeded: = int(getP("luckt"))
onready var bonusDam: = getP("dam")
onready var luck: = int(getP("luck"))

func onDealtDamage(damageRes: DamageResult):
	
	if damageRes.hasHit():
		if tryUseLucky(luckNeeded, damageRes.event):
			addBonusDamage(bonusDam)
			var particles = ObjectPool.particleOneShot(activationParticles, sprite)
			particles.rotation_degrees = 90
			particles.position = Vector2(4, 178)
	else:
		giveLucky(luck, damageRes.event)
		var particles = ObjectPool.particleOneShot(activationParticles, sprite)
		particles.rotation_degrees = - 90
		particles.position = Vector2(4, - 262)
	
