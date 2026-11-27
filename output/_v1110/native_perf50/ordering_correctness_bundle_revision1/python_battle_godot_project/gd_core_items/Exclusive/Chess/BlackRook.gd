extends ChessPiece
var buffTimer
var spikes
var crit

func doCapturingEffect(_eliminatedPiece):
	return giveSpikes(spikes)


func doEliminatedEffect(_capturingPiece):
	changeAllItemsCritRate(crit)
	buffTimer.start(getP_m("dur"))


func buffEnded():
	changeAllItemsCritRate( - crit)

func _readyInit():
	._readyInit()
	buffTimer = newItemTimer("BuffTimer", "buffEnded", false)
	spikes = int(getP("spikes"))
	crit = getP("crit")
