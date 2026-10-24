extends Weapon

func canAffect(item):
	return item.hasCooldown()
	
func onCombatStart():
	for item in getAffectedItems():
		item.addSpeed(getP1() / 100)
	
	activate(null, false)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		var res: DamageResult = dealDamage()
		activate(res, false)
		var res2 = dealDamage()
		activate(res2, false)
		var hits = 0
		if res.hasHit():
			hits += 1
		if res2.hasHit():
			hits += 1
		
		var ani = createAnimation()
		ani.randomizePosition()
		if hits == 2:
			ani.animation.play("DoubleHit")
		elif hits == 1:
			ani.animation.play("SingleHit")
		else:
			ani.animation.play("Miss")

func getCraftingOffset(forDirection):
	match forDirection:
		FaceDirection.UP:
			return Vector2(0, - 1)
		FaceDirection.DOWN:
			return Vector2.ZERO
		FaceDirection.LEFT:
			return Vector2( - 1, 0)
		FaceDirection.RIGHT:
			return Vector2.ZERO
