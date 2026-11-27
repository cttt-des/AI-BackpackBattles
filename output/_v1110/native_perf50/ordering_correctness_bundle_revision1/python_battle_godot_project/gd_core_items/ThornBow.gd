extends Bow
var bonusCounter = 0
var tempBonusDam: int

func hasAttackEffect() -> bool:
	return true


func onPrepare():
	bonusCounter = 0
	setState(bonusCounter)


func onCombatStart():
	giveSpikes(getP1())
	activate(null, false)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		var res: CoreDamageResult = dealDamage()
		activate(res)
		
		if bonusCounter > 0:
			reduceBonusDamage(tempBonusDam * bonusCounter, false)
			bonusCounter = 0
			setState(bonusCounter, false, res.event)


func onWeaponAttacked(damageRes: CoreDamageResult):
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
		pass
	else:
		pass

func _readyInit():
	._readyInit()
	tempBonusDam = getP2()
