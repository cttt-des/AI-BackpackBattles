extends Item
const firstKnightRound = 1
const firstRookRound = 6
const firstQueenRound = 14
var speed_v

func onPrepare():
	var chessboards = getAllInInventoryOfType(ctx.item_book.getDescriptor("Chess Board"))
	if not chessboards.empty():
		chessboards[0].addSpeed(speed_v)


func onShopEntered():
	pass

func _readyInit():
	._readyInit()
	speed_v = getP("speed") / 100.0
