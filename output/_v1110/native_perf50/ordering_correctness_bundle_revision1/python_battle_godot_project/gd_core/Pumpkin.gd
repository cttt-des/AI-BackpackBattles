extends Food
var heat
var normalTexture

func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		var res = dealDamage()
		activate(res)


func onPrepare():
	descriptor.activationAni = ActivationAni.Throw
	connectForCombat(ctx.combat, "fatigue_start", "onFatigueStarted")


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		stun(getP_m("dur_stun"), damageRes.event)


func onFatigueStarted():
	giveHeat(heat)
	activate()


func onShopEntered():
	pass

func _readyInit():
	._readyInit()
	heat = int(getP("heat"))
	damageSource = CoreDamageSource.new().setItem(self)

