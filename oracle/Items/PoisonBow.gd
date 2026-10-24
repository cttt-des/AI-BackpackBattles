extends Bow

onready var damagePerPoison: int = getP1()
var damageAcc: int = 0

func hasAttackEffect() -> bool:
	return true

func onPrepare():
	connectForCombat(opponent(), "character_poison_changed", "onOpponentPoisonChanged")
	damageAcc = 0

func onWeaponAttacked(damageRes: DamageResult):
	if damageRes.hasHit():
		
		var attackEffectCount = 1 + rollDoubleAttackEffect()
		for i in attackEffectCount:
			damageAcc += damageRes.damage
	
		setState(damageAcc, false, damageRes.event)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		
		var poisonStacks = damageAcc / damagePerPoison
		var poisonEvent = inflictPoison(poisonStacks)
		damageAcc %= damagePerPoison
		setState(damageAcc, false, poisonEvent)
		
		var res: DamageResult = dealDamage()
		activate(res)

func onOpponentPoisonChanged(amount, _event):
	changeVaryingDamage(amount * getP2())

func onShopEntered():
	onStateChanged(0)

func onStateChanged(_damageAcc):
	if _damageAcc < damagePerPoison:
		activationParticles.deactivate()
		light.hide()
	else:
		activationParticles.activate()
		var poisonStacks = _damageAcc / damagePerPoison
		activationParticles.scale = Vector2.ONE * min(1.2, 0.5 + 0.2 * poisonStacks)
		light.show()

