extends Item

func canAffect(item):
	return item.hasTag(Tag.Stone)

func onPrepare():
	for item in getAffectedItems():
		item.setBagOfStones()

func getAffectedCellsAfterRotate_primary(rotatedCells) -> Array:
	return Game.PLAYER.INVENTORY.getCellsInLine(rotatedCells, Vector2.UP, 1)
	
