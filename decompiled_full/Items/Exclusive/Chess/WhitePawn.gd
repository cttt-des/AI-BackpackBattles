extends ChessPiece

onready var luck: = int(getP("luck"))
onready var regen: = int(getP("regen"))

func doCapturingEffect(_eliminatedPiece):
	return giveRegeneration(regen)

func doEliminatedEffect(_capturingPiece):
	giveLucky(luck)
