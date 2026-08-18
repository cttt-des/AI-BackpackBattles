extends ChessPiece

onready var buffTimer = $BuffTimer
onready var damReduction: = getP("dam")

func doCapturingEffect(_eliminatedPiece):
	return giveBlock()

func doEliminatedEffect(_capturingPiece):
	character().changeDamageResistance(damReduction)
	buffTimer.start(getP_m("dur"))
	
func buffEnded():
	character().changeDamageResistance( - damReduction)
