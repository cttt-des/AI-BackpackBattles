extends ChessPiece
var buffTimer
var damReduction

func doCapturingEffect(_eliminatedPiece):
	return giveBlock()


func doEliminatedEffect(_capturingPiece):
	character().changeDamageResistance(damReduction)
	buffTimer.start(getP_m("dur"))
	

func buffEnded():
	character().changeDamageResistance( - damReduction)

func _readyInit():
	._readyInit()
	buffTimer = newItemTimer("BuffTimer", "buffEnded", false)
	damReduction = getP("dam")
