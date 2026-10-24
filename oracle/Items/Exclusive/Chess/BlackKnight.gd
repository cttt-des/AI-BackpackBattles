extends ChessPiece

onready var vampirism: = int(getP("vampirism"))
onready var stamina: = getP("stamina")

func doCapturingEffect(_eliminatedPiece):
	return giveVampirism(vampirism)

func doEliminatedEffect(_capturingPiece):
	drainStamina(stamina)

func canBeBlocked() -> bool:
	return false
