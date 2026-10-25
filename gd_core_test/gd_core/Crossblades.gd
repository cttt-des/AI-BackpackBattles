extends Weapon

func canAffect(item):
	return item.canBeEmpowered()


func canAffect_secondary(item):
	return item.hasCooldown()


func onCombatStart():
	for item in getAffectedItems(CoreConst.Affected.Primary):
		item.addBonusDamage(getP1())
	
	for item in getAffectedItems(CoreConst.Affected.Secondary):
		item.addSpeed(getP2() / 100.0)
	
	activate(null, false)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		addBonusDamage(getP3())
		addSpeed(getP4() / 100.0)


func getCraftingOffset(forDirection):
	match forDirection:
		CoreConst.FaceDirection.UP:
			return Vector2( - 1, 0)
		CoreConst.FaceDirection.DOWN:
			return Vector2( - 1, 0)
		CoreConst.FaceDirection.LEFT:
			return Vector2(0, - 1)
		CoreConst.FaceDirection.RIGHT:
			return Vector2(0, - 1)

func _readyInit():
	._readyInit()
	pass
