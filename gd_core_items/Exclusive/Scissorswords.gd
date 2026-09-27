extends "res://gd_core_items/Lightsaber.gd"
var luckNeeded
var bonusDam
var luck
var regen

func inflict(duration, event):
	.inflict(duration, event)
	giveStacksTemporary(character(), CoreConst.EventType.Blind, 
		blind, duration, event)


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if character().getLucky() >= luckNeeded:
			var event = useLucky(luckNeeded, damageRes.event)
			addBonusDamage(bonusDam)
			giveRegeneration(regen, event)
	else:
		giveLucky(luck, damageRes.event)

func _readyInit():
	._readyInit()
	luckNeeded = int(getP("luckt"))
	bonusDam = getP("dam")
	luck = int(getP("luck"))
	regen = int(getP("regen"))
