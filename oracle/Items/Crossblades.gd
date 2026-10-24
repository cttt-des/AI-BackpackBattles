extends Weapon

func canAffect(item):
	return item.canBeEmpowered()

func canAffect_secondary(item):
	return item.hasCooldown()

func onCombatStart():
	for item in getAffectedItems(Affected.Primary):
		item.addBonusDamage(getP1())
	
	for item in getAffectedItems(Affected.Secondary):
		item.addSpeed(getP2() / 100.0)
	
	activate(null, false)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		addBonusDamage(getP3())
		addSpeed(getP4() / 100.0)

func getCraftingOffset(forDirection):
	match forDirection:
		FaceDirection.UP:
			return Vector2( - 1, 0)
		FaceDirection.DOWN:
			return Vector2( - 1, 0)
		FaceDirection.LEFT:
			return Vector2(0, - 1)
		FaceDirection.RIGHT:
			return Vector2(0, - 1)
