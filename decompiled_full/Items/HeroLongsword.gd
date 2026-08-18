extends Weapon

func canAffect(item):
	return item.canBeEmpowered()

func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(getP1())
	activate(null, false)

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
