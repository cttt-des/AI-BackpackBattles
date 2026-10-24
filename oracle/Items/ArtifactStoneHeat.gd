extends "res://Items/Stone.gd"

var dmgBonusActive: bool
onready var activationParticles = $Icon / ActivationParticles

func canAffect(item):
	return item.canBeEmpowered()

func onPrepare():
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")
	dmgBonusActive = false

func onHeatChanged(amount, event):
	if not dmgBonusActive and amount > 0:
		if character().getHeat() >= getP2():
			dmgBonusActive = true
			activationParticles.activate()
			for weapon in getAffectedItems():
				weapon.addBonusDamage(getP3())

func onCombatEnd():
	activationParticles.deactivate()

func preHit():
	giveHeat(getP1())
