extends Weapon

onready var damPerDebuff = getP1()

func onPrepare():
	connectToOpponentDebuffs("onDebuffsChanged")

func onDebuffsChanged(amount, _event):
	changeVaryingDamage(amount * damPerDebuff)

func onPreDealDamage_early(damageRes: DamageResult):
	var event = tryUseMana(getP2())
	if event != null:
		inflictBlind(getP3(), event)
