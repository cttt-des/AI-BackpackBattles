extends "res://Items/Greatsword.gd"

const activationParticles = preload("res://Items/Exclusive/Particles/BigBloodthorneActivationParticles.tscn")

onready var damPerVampOrSpike: = getP("dam")
onready var regenNeeded: = int(getP("regent"))
onready var vampirism: = int(getP("vampirism"))
onready var spikes: = int(getP("spikes"))

func onPrepare():
	.onPrepare()
	connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")

func onVampirismChanged(amount, _event):
	changeVaryingDamage(amount * damPerVampOrSpike)

func onSpikesChanged(amount, _event):
	changeVaryingDamage(amount * damPerVampOrSpike)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		if character().getRegeneration() >= regenNeeded:
			useRegeneration(regenNeeded)
			giveVampirism(vampirism)
			giveSpikes(spikes)
			ObjectPool.particleOneShot(activationParticles, sprite)
