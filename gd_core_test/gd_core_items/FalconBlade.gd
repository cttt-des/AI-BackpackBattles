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
