extends ChessPiece


onready var heat: = int(getP("heat2"))
onready var heatFirstCapture: = int(getP("heat1"))

func doCapturingEffect(_eliminatedPiece):
	if numCaptures == 1:
		return giveHeat(heatFirstCapture)
	else:
		return giveHeat(heat)

func doEliminatedEffect(_capturingPiece):
	character().makeInvulnerable(getP_m("dur"), self)
