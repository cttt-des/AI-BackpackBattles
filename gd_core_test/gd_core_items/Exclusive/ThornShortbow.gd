extends Weapon

func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		giveSpikes(1, damageRes.event)

func _readyInit():
	._readyInit()
	pass
