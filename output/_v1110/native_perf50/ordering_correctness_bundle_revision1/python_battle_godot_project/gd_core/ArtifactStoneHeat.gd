extends "res://gd_core_items/Stone.gd"
var dmgBonusActive: bool
var activationParticles

func canAffect(item):
	return item.canBeEmpowered()


func onPrepare():
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")
	dmgBonusActive = false


func onHeatChanged(amount, event):
	if not dmgBonusActive and amount > 0:
		if character().getHeat() >= getP2():
			dmgBonusActive = true
			for weapon in getAffectedItems():
				weapon.addBonusDamage(getP3())


func onCombatEnd():
	pass


func preHit():
	giveHeat(getP1())

func _readyInit():
	._readyInit()
	pass
