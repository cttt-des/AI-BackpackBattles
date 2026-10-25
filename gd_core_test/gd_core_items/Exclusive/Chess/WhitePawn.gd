extends ChessPiece
var luck
var regen

func doCapturingEffect(_eliminatedPiece):
	return giveRegeneration(regen)


func doEliminatedEffect(_capturingPiece):
	giveLucky(luck)

func _readyInit():
	._readyInit()
	luck = int(getP("luck"))
	regen = int(getP("regen"))
