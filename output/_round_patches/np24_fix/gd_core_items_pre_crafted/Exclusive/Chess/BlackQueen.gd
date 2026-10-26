extends ChessPiece
var buffs

func doCapturingEffect(_eliminatedPiece):
	if numCaptures == 1:
		return stealRandomBuff(buffs)
	else:
		return stealRandomBuff(1)


func doEliminatedEffect(_capturingPiece):
	stun(getP_m("dur"))

func _readyInit():
	._readyInit()
	buffs = int(getP("buffs"))
