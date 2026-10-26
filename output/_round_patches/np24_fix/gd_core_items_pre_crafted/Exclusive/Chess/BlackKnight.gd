extends ChessPiece
var vampirism
var stamina

func doCapturingEffect(_eliminatedPiece):
	return giveVampirism(vampirism)


func doEliminatedEffect(_capturingPiece):
	drainStamina(stamina)


func canBeBlocked() -> bool:
	return false

func _readyInit():
	._readyInit()
	vampirism = int(getP("vampirism"))
	stamina = getP("stamina")
