extends ChessPiece

onready var buffTimer = $BuffTimer
onready var spikes: = int(getP("spikes"))
onready var crit: = getP("crit")

func doCapturingEffect(_eliminatedPiece):
	return giveSpikes(spikes)

func doEliminatedEffect(_capturingPiece):
	changeAllItemsCritRate(crit)
	buffTimer.start(getP_m("dur"))

func buffEnded():
	changeAllItemsCritRate( - crit)
