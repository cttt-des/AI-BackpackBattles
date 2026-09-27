extends Item
const firstKnightRound = 1
const firstRookRound = 6
const firstQueenRound = 14
var speed

func onPrepare():
	var chessboards = getAllInInventoryOfType(ctx.item_book.getDescriptor("Chess Board"))
	if not chessboards.empty():
		chessboards[0].addSpeed(speed)


func onShopEntered():
	pass

func _readyInit():
	._readyInit()
	speed = getP("speed") / 100.0
