extends Weapon

var enteredRage = false

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		
		if enteredRage:
			addBonusDamage(getP2())
		else:
			addBonusDamage(getP1())

func onPrepare():
	enteredRage = false
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")

func onBattleRageStarted(event):
	doCooldownEffect()
	enteredRage = true
