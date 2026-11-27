extends "res://gd_core_items/RibSawBlade.gd"
var buffsNeeded
var removeBuffs

func onPreDealDamage_early(damageRes: CoreDamageResult):
	.onPreDealDamage_early(damageRes)
	if damageRes.hasHit():
		var buffs = opponent().getBuffStacks()
		if buffs >= buffsNeeded:
			removeMostBuffs(removeBuffs)

func _readyInit():
	._readyInit()
	buffsNeeded = int(getP("buffst"))
	removeBuffs = int(getP("buffs"))
