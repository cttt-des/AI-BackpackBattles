extends ChessPiece
var boardSpeed
var stamina

func doCapturingEffect(_eliminatedPiece):
	board.addSpeed(boardSpeed)
	


func doEliminatedEffect(_capturingPiece):
	giveMaxStaminaTemporary(stamina)


func canBeBlocked() -> bool:
	return false

func _readyInit():
	._readyInit()
	boardSpeed = getP("speed") / 100.0
	stamina = getP("stamina")
