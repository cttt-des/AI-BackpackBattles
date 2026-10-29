extends Weapon

func canAffect(item):
	return item.hasCooldown()
	

func onCombatStart():
	for item in getAffectedItems():
		item.addSpeed(getP1() / 100)
	
	activate(null, false)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		var res: CoreDamageResult = dealDamage()
		activate(res, false)
		var res2 = dealDamage()
		activate(res2, false)
		var hits = 0
		if res.hasHit():
			hits += 1
		if res2.hasHit():
			hits += 1
		
		if hits == 2:
			pass
		elif hits == 1:
			pass
		else:
			pass

		# ★ RNG 链消耗还原（r2_1）：decomp Items/FalconBlade.gd:24-25 createAnimation()+ani.randomizePosition() ——
		#   ItemAnimation.gd:26-28 恒抽 3 次（(30,100)/5.0 export 默认；直调不经 intialize 无 playback_speed）。
		#   run631_r9/701_r11/722_r7 逐抽对位实证 + 台账第 24 轮 run634 同根。
		ctx.rng.randf_range( - 30.0, 30.0)
		ctx.rng.randf_range( - 100.0, 100.0)
		ctx.rng.randf_range( - 5.0, 5.0)


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
	pass
