extends Weapon

func canAffect(item):
	return item.canBeEmpowered()


func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(getP1())
	activate(null, false)


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
