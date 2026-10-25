extends Weapon

func canAffect(item):
	return item.hasType(CoreConst.Type.Food)


func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onFoodActivated")
	
	opponent().changePoisonCritChancePercent(getNumAffectedItems() * getChance())


func onFoodActivated(event):
	
	inflictPoison(getP1())


func getCraftingOffset(forDirection):
	match forDirection:
		CoreConst.FaceDirection.UP:
			return Vector2( - 1, 1)
		CoreConst.FaceDirection.DOWN:
			return Vector2.ZERO
		CoreConst.FaceDirection.LEFT:
			return Vector2(1, 0)
		CoreConst.FaceDirection.RIGHT:
			return Vector2(0, - 1)

func _readyInit():
	._readyInit()
	pass
