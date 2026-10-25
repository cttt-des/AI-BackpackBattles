extends ChessPiece
var heat
var heatFirstCapture

func doCapturingEffect(_eliminatedPiece):
	if numCaptures == 1:
		return giveHeat(heatFirstCapture)
	else:
		return giveHeat(heat)


func doEliminatedEffect(_capturingPiece):
	character().makeInvulnerable(getP_m("dur"), self)

func _readyInit():
	._readyInit()
	heat = int(getP("heat2"))
	heatFirstCapture = int(getP("heat1"))
