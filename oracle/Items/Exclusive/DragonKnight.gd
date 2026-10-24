extends "res://Items/RubyWhelp.gd"

onready var cdAdvance: = getP("advance")

func canAffect(item):
	return item.canActivate()

func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")

func onDealtDamage(damageRes):
	if damageRes.hasHit():
		heal(getP_m("heal"), damageRes.event)

func onItemActivated(event):
	advanceCooldownPercent(cdAdvance)
