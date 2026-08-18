extends Bow


var extraAttack = false

func onPrepare():
	setState(false)

func onCombatStart():
	giveLucky(getP1())
	activate(null, false)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		var res: DamageResult = dealDamage()
		activate(res)
		if extraAttack:
			var res2 = dealDamage(res.event)
			activate(res2)
			setState(false, false, res2.event)

func onWeaponAttacked(damageRes: DamageResult):
	if damageRes.wasCriticalHit():
		setState(true, false, damageRes.event)

func onShopEntered():
	onStateChanged(false)

func onStateChanged(_extraAttack):
	if _extraAttack:
		activationParticles.activate()
		light.show()
	else:
		activationParticles.deactivate()
		light.hide()
	
	extraAttack = _extraAttack
