extends Weapon

func canAffect(item):
	return item.hasType(Type.Food)

func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onFoodActivated")
	
	opponent().changePoisonCritChancePercent(getNumAffectedItems() * getChance())

func onFoodActivated(event):
	
	inflictPoison(getP1())

func getCraftingOffset(forDirection):
	match forDirection:
		FaceDirection.UP:
			return Vector2( - 1, 1)
		FaceDirection.DOWN:
			return Vector2.ZERO
		FaceDirection.LEFT:
			return Vector2(1, 0)
		FaceDirection.RIGHT:
			return Vector2(0, - 1)
