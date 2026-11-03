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
		
		# ★ np29fI（同 RubyChonk 定谳）：原版攻击尾 createAnimation+randomize
		#   Position（Item.gd:5336/Animations/ItemAnimation.gd:26-28）= 3 笔
		#   Util.rng 裸抽不入账；内核此前整块剥离 → 每双击缺 6 步。
		ctx.rng.rng.randf_range(-30.0, 30.0)
		ctx.rng.rng.randf_range(-100.0, 100.0)
		ctx.rng.rng.randf_range(-5.0, 5.0)


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
