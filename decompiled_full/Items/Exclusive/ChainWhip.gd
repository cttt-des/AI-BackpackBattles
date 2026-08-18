extends Weapon

var buffsPurged = 0

func onPrepare():
	buffsPurged = 0
	connectToOpponentBuffs("onOpponentBuffsChanged")

func onOpponentBuffsChanged(amount, event):
	if amount < 0:
		if event.getOrigin() is Item and event.getOrigin().character() == character():
			buffsPurged += - amount
			addBonusDamage( - amount * getP3())

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		removeRandomBuffs(getP1())
		if character().isBattleRaging():
			heal()
