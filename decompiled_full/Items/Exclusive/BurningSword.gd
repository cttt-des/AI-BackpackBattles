extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/BurningSwordActivationParticles.tscn")

var heatCounter = 0
var particleReadyTime: = 0.0

onready var heatOnHit: int = getP1()
onready var heatNeeded: int = getP2()

func canAffect(item):
	return item.canBeEmpowered()

func onPrepare():
	heatCounter = 0
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")

func onHeatChanged(amount, _event):
	if amount > 0:
		heatCounter += amount
		var bonus = heatCounter / heatNeeded
		if bonus > 0:
			var bonusDamage = getP3() * bonus
			for item in getAffectedItems():
				item.addBonusDamage(bonusDamage)
			addBonusDamage(bonusDamage)
			
			if Util.time >= particleReadyTime:
				ObjectPool.particleOneShot(activationParticles, sprite)
				particleReadyTime = Util.time + 0.1
		
		heatCounter %= heatNeeded

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		giveHeat(heatOnHit)
