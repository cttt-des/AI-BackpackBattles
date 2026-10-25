extends ChessPiece
var debuffs
var healReduction
var maxHealthReduction

func doCapturingEffect(_eliminatedPiece):
	return inflictRandomDebuffs(debuffs)


func doEliminatedEffect(_capturingPiece):
	opponent().reduceHealingEfficiency(healReduction)
	opponent().changeMaxHealthGain(maxHealthReduction)
	

func _readyInit():
	._readyInit()
	debuffs = int(getP("debuffs"))
	healReduction = getP("healreduction") / 100.0
	maxHealthReduction = - getP("healthreduction") / 100.0
