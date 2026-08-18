extends Weapon

const activationParticlesScene = preload("res://Items/Exclusive/Particles/ObsidianDragonActivationParticles.tscn")

var heatCounter = 0
var affectedWeapon = null
onready var heatNeeded = int(getP1())
onready var bonusDam = int(getP2())

func canAffect(item):
	return item.canBeEmpowered()

func onPrepare():
	affectedWeapon = getFirstAffectedItem()
	heatCounter = 0
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")

func onHeatChanged(amount, event):
	if amount > 0:
		heatCounter += amount
		var proccs = heatCounter / heatNeeded
		if proccs > 0:
			heatCounter %= heatNeeded
			
			addBonusDamage(bonusDam * proccs)
			if affectedWeapon != null:
				affectedWeapon.addCritTokens(proccs)
				ObjectPool.particleOneShot(activationParticlesScene, self)
