extends Bow
var extraAttack = false

func onPrepare():
	setState(false)


func onCombatStart():
	giveLucky(getP1())
	activate(null, false)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		var res: CoreDamageResult = dealDamage()
		activate(res)
		if extraAttack:
			var res2 = dealDamage(res.event)
			activate(res2)
			setState(false, false, res2.event)


func onWeaponAttacked(damageRes: CoreDamageResult):
	if damageRes.wasCriticalHit():
		setState(true, false, damageRes.event)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(_extraAttack):
	if _extraAttack:
		pass
	else:
		pass
	
	extraAttack = _extraAttack

func _readyInit():
	._readyInit()
	pass
