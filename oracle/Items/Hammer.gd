extends Weapon

const stunParticles = preload("res://Items/Particles/StunParticles.tscn")

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		stun(getP_m("dur_stun"), damageRes.event)
		var particles = ObjectPool.particleOneShot(stunParticles, sprite)
		particles.position = Vector2(175, - 144)

func onFusingAsCatalystFinished():
	.onFusingAsCatalystFinished()
	playActivationAnimation()
