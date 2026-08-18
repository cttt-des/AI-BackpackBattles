extends Bow

onready var tempBonusDam: int = getP2()
var bonusCounter = 0

func hasAttackEffect() -> bool:
	return true

func onPrepare():
	bonusCounter = 0
	setState(bonusCounter)

func onCombatStart():
	giveSpikes(getP1())
	activate(null, false)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		var res: DamageResult = dealDamage()
		activate(res)
		
		if bonusCounter > 0:
			reduceBonusDamage(tempBonusDam * bonusCounter, false)
			bonusCounter = 0
			setState(bonusCounter, false, res.event)

func onWeaponAttacked(damageRes: DamageResult):
	if damageRes.hasHit():
		var attackEffectCount = 1 + rollDoubleAttackEffect()
		for i in attackEffectCount:
			if character().getSpikes() > 0:
				bonusCounter += 1
				useSpikes(1, damageRes.event)
				addBonusDamage(tempBonusDam)
		setState(bonusCounter, false, damageRes.event)

func onShopEntered():
	onStateChanged(0)

func onStateChanged(_bonusCounter):
	if _bonusCounter > 0:
		activationParticles.activate()
		activationParticles.scale = Vector2.ONE * min(3, 1.5 + 0.5 * bonusCounter)
		light.show()
	else:
		activationParticles.deactivate()
		light.hide()
