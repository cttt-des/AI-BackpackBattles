extends Item

onready var speed: = getP("speed") / 100.0

func onPrepare():
	var chessboards = getAllInInventoryOfType(ItemBook.chessboardDescriptor)
	if not chessboards.empty():
		chessboards[0].addSpeed(speed)

const firstKnightRound = 1
const firstRookRound = 6
const firstQueenRound = 14


func onShopEntered():
	var chessboards = getAllInInventoryOfType(ItemBook.chessboardDescriptor)
	if not chessboards.empty():
		var weights = [0, 0, 0, 0, 0, 0]
		var roundsPassed = Game.curRound - Game.SKILL_ROUND1
		weights[0] = 2
		weights[1] = (roundsPassed - firstKnightRound) * 2 if roundsPassed > firstKnightRound else 0
		weights[2] = weights[1]
		weights[3] = (roundsPassed - firstRookRound) * 2 if roundsPassed > firstRookRound else 0
		weights[4] = 5 if roundsPassed >= firstQueenRound else 0
		weights[5] = weights[3]
		
		var bag = WeightedBag.new()
		var index = bag.rollOnce(weights)
		var pieceDescriptor
		if Util.roll():
			pieceDescriptor = chessboards[0].blackPieces[index]
		else:
			pieceDescriptor = chessboards[0].whitePieces[index]
		var piece = ItemBook.generateItem(pieceDescriptor)
		var adjacentCells = inventory.getAdjacentCells(occupiedCells)
		placeGeneratedItem(piece, adjacentCells)
		activate(null, false)
		Game.saveRunState()
