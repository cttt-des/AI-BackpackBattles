extends ChessPiece
var mana
var poison

func doCapturingEffect(eliminatedPiece):
	return giveMana(mana)
	
	


func doEliminatedEffect(_capturingPiece):
	inflictPoison(poison)

func _readyInit():
	._readyInit()
	mana = int(getP("mana"))
	poison = int(getP("poison"))
