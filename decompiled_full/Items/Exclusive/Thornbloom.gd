extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/ThornbloomActivationParticles.tscn")

onready var spikes: int = getP("spikes")
onready var empower: int = getP("empower")
onready var damPerSpike = getP("damperspike")

func onPrepare():
	connectForCombat(character(), "character_empower_changed", "onEmpowerChanged")
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")

func onSpikesChanged(amount, _event):
	changeVaryingDamage(damPerSpike * amount)

func onEmpowerChanged(amount, event):
	if amount > 0:
		giveMaxHealth(getP_m("maxhealth") * amount, event)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		giveSpikes(spikes)
		
		var particles = ObjectPool.particleOneShot(activationParticles, sprite)
		if rollChance():
			giveEmpower(empower)
			particles.modulate = Color(0.6, 1.1, 0.2)
		else:
			particles.modulate = Color(0.4, 1.4, 0.2)
