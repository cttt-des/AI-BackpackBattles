extends Bag

onready var speedReduction = getP("speedreduction") / 100.0
onready var damBonusFactor = getP("dambonus") / 100.0

func canLockBag():
	return true

func canApplyEffect(toItem):
	return toItem.canBeEmpowered()

func onPrepare():
	
	
	connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")

func onCombatStart():
	for item in getItemsInside():
		if canApplyEffect(item):
			item.reduceSpeed(speedReduction)
			item.addBonusDamageFactor(damBonusFactor)

func onOpponentDamaged(damageRes: DamageResult):
	if character().isBattleRaging():
		if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
			heal(ceil(getP_m("lifesteal") / 100.0 * damageRes.damage), damageRes.event)







func doCooldownEffect():
	character().startBattleRage(self, getP_m("dur_rage"))
	onAfterEffectFinished()
