extends ChessPiece

onready var debuffs: = int(getP("debuffs"))
onready var healReduction: = getP("healreduction") / 100.0
onready var maxHealthReduction: = - getP("healthreduction") / 100.0

func doCapturingEffect(_eliminatedPiece):
	return inflictRandomDebuffs(debuffs)

func doEliminatedEffect(_capturingPiece):
	opponent().reduceHealingEfficiency(healReduction)
	opponent().changeMaxHealthGain(maxHealthReduction)
	
