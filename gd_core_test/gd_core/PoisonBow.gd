extends Bow
var damageAcc: int = 0
var damagePerPoison: int

func hasAttackEffect() -> bool:
	return true


func onPrepare():
	connectForCombat(opponent(), "character_poison_changed", "onOpponentPoisonChanged")
	damageAcc = 0


func onWeaponAttacked(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		
		var attackEffectCount = 1 + rollDoubleAttackEffect()
		for i in attackEffectCount:
			damageAcc += damageRes.damage
	
		setState(damageAcc, false, damageRes.event)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		
		var poisonStacks = damageAcc / damagePerPoison
		var poisonEvent = inflictPoison(poisonStacks)
		damageAcc %= damagePerPoison
		setState(damageAcc, false, poisonEvent)
		
		var res: CoreDamageResult = dealDamage()
		activate(res)


func onOpponentPoisonChanged(amount, _event):
	changeVaryingDamage(amount * getP2())


func onShopEntered():
	onStateChanged(0)


func onStateChanged(_damageAcc):
	if _damageAcc < damagePerPoison:
		pass
	else:
		var poisonStacks = _damageAcc / damagePerPoison

func _readyInit():
	._readyInit()
	damagePerPoison = getP1()
