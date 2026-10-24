extends ChessPiece


onready var mana: = int(getP("mana"))
onready var poison: = int(getP("poison"))

func doCapturingEffect(eliminatedPiece):
	return giveMana(mana)
	
	

func doEliminatedEffect(_capturingPiece):
	inflictPoison(poison)
