extends ChessPiece
var cleanses
var healamp

func doCapturingEffect(_eliminatedPiece):
	return cleanseRandomDebuffs(cleanses)


func doEliminatedEffect(_capturingPiece):
	character().addHealingEfficiency(healamp)

func _readyInit():
	._readyInit()
	cleanses = int(getP("cleanse"))
	healamp = getP("healamp") / 100.0
