extends Weapon
var heatThresholdReached: bool
var hasStunned: bool
var activationParticles
var heatThreshold

func onPrepare():
	setState(false)
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")


func onHeatChanged(amount, event):
	if not heatThresholdReached:
		if character().getHeat() >= heatThreshold:
			setState(true, false, event)
	elif character().getHeat() < heatThreshold:
		setState(false, false, event)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		hasStunned = false
		var res: CoreDamageResult = dealDamage()
		if hasStunned:
			activate(res, false, false, ActivationAni.Tackle)
		else:
			activate(res, false)
		if res.hasHit():
			if hasStunned:
				pass
			else:
				pass
		else:
			pass


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		giveHeat(1, damageRes.event)
		if heatThresholdReached:
			if rollChance():
				stun(getP_m("dur_stun"), damageRes.event)
				hasStunned = true


func onShopEntered():
	onStateChanged(false)


func onStateChanged(_heatThresholdReached):
	if _heatThresholdReached:
		pass
	else:
		pass
	
	heatThresholdReached = _heatThresholdReached


func getCraftingOffset(forDirection):
	match forDirection:
		CoreConst.FaceDirection.UP:
			return Vector2(0, - 1)
		CoreConst.FaceDirection.DOWN:
			return Vector2.ZERO
		CoreConst.FaceDirection.LEFT:
			return Vector2( - 1, 0)
		CoreConst.FaceDirection.RIGHT:
			return Vector2.ZERO

func _readyInit():
	._readyInit()
	heatThreshold = int(getP1())
