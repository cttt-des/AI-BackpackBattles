extends Item

func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		var res = dealDamage()
		activate(res)

func _readyInit():
	._readyInit()
	damageSource = CoreDamageSource.new().setItem(self)

