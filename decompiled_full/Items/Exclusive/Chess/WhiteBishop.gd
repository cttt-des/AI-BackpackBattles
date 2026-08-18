extends ChessPiece

onready var cleanses: = int(getP("cleanse"))
onready var healamp: = getP("healamp") / 100.0

func doCapturingEffect(_eliminatedPiece):
	return cleanseRandomDebuffs(cleanses)

func doEliminatedEffect(_capturingPiece):
	character().addHealingEfficiency(healamp)
