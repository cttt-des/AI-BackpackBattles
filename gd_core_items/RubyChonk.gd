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
		# ★ np29fI（run1514_r18 fd@36 定谳）：原版攻击尾的攻击动画块在此处照常
		#   消耗主链——`var ani = createAnimation(); ani.randomizePosition()`
		#   （Item.gd:5336-5353 + Animations/ItemAnimation.gd:26-28）：
		#   createAnimation=ObjectPool.instance（零抽）+ randomizePosition=
		#   Util.rng.randf_range ×3 **裸调不入账**（rng_log 零痕迹，与 np24
		#   ItemAnimation 同款）。内核此前整块剥离 → 每攻击缺 3 抽；另有尾随
		#   1 抽（PCG 解算 oracle 在 randomizePosition 与下一拍 adjustCooldown
		#   之间恒多 2 步，调用点未名——数值不入事件流，仅链位推进）。3 笔合计
		#   6 步/攻击（IRND 探针态==row218 post 实证；playback_speed 属 intialize、
		#   RC 走 createAnimation+randomizePosition 直调不含它）。实证：run1514 oracle 在 RC 攻击#1 激活音与攻击#2
		#   adjustCooldown 之间恰多 8 步（状态前向解算 adv0→adv8），gd trace
		#   同窗 0 抽（ANIMDBG pc=False as=True——RC 的 activate(res,false)
		#   playCombatAni 闸本来就不走 ANIM 块，块在 doCooldownEffect 尾）。
		ctx.rng.rng.randf_range(-30.0, 30.0)
		ctx.rng.rng.randf_range(-100.0, 100.0)
		ctx.rng.rng.randf_range(-5.0, 5.0)


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
