extends Weapon
var damPerDebuff

func onPrepare():
	connectToOpponentDebuffs("onDebuffsChanged")


func onDebuffsChanged(amount, _event):
	changeVaryingDamage(amount * damPerDebuff)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	var event = tryUseMana(getP2())
	if event != null:
		inflictBlind(getP3(), event)

func _readyInit():
	._readyInit()
	damPerDebuff = getP1()
