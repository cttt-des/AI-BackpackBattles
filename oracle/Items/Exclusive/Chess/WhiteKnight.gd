extends ChessPiece


onready var boardSpeed: = getP("speed") / 100.0
onready var stamina: = getP("stamina")

func doCapturingEffect(_eliminatedPiece):
	board.addSpeed(boardSpeed)
	

func doEliminatedEffect(_capturingPiece):
	giveMaxStaminaTemporary(stamina)

func canBeBlocked() -> bool:
	return false
