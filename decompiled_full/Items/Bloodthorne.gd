extends Weapon

const activationParticles = preload("res://Items/Particles/BloodthorneActivationParticles.tscn")

onready var regenNeeded: = int(getP1())
onready var vampirism: = int(getP2())
onready var spikes: = int(getP3())

func onPrepare():
	connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")

func onVampirismChanged(amount, _event):
	changeVaryingDamage(amount)

func onSpikesChanged(amount, _event):
	changeVaryingDamage(amount)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		var numRegen = character().getRegeneration()
		if numRegen >= regenNeeded:
			var event = useRegeneration(regenNeeded)
			giveVampirism(vampirism, event)
			giveSpikes(spikes, event)
			ObjectPool.particleOneShot(activationParticles, sprite)
