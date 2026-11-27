extends Item

func canAffect(item):
	return item.hasTag(CoreConst.Tag.Stone)


func onPrepare():
	for item in getAffectedItems():
		item.setBagOfStones()


func getAffectedCellsAfterRotate_primary(rotatedCells) -> Array:
	return ctx.player.INVENTORY.getCellsInLine(rotatedCells, Vector2.UP, 1)
	

func _readyInit():
	._readyInit()
	pass
