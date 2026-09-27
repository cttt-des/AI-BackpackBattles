extends Weapon

func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		stun(getP_m("dur_stun"), damageRes.event)


func onFusingAsCatalystFinished():
	.onFusingAsCatalystFinished()
	playActivationAnimation()

func _readyInit():
	._readyInit()
	pass
