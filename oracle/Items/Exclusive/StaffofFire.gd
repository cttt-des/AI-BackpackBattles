extends Weapon

onready var activationParticles = $Icon / ActivationParticles

onready var manaCost: int = getP1()
onready var heatCost: int = getP2()
onready var damBonus: int = getP3()
var numActivations: int

func _ready() -> void :
	activationParticles.process_material = activationParticles.process_material.duplicate()

func onPrepare():
	numActivations = 0

func onPreDealDamage_early(damageRes: DamageResult):
	if character().getHeat() >= heatCost:
		var event = tryUseMana(manaCost)
		if event != null:
			useHeat(heatCost, event)
			addBonusDamage(damBonus)
			numActivations += 1
			activationParticles.activate()
			activationParticles.process_material.scale = min(
					1.4, 0.4 + sqrt(numActivations) * 0.3)

func onShopEntered():
	activationParticles.deactivate()
