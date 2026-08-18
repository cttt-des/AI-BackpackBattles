extends ChessPiece

onready var buffs: = int(getP("buffs"))

func doCapturingEffect(_eliminatedPiece):
	if numCaptures == 1:
		return stealRandomBuff(buffs)
	else:
		return stealRandomBuff(1)

func doEliminatedEffect(_capturingPiece):
	stun(getP_m("dur"))
