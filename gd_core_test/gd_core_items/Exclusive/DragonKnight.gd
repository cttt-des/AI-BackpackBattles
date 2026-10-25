extends "res://gd_core_items/RubyWhelp.gd"
var cdAdvance

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

func _readyInit():
	._readyInit()
	cdAdvance = getP("advance")
