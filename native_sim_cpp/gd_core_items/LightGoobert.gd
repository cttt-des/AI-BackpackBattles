extends Goobert
var particleTimer
var activationParticles
var blindAmount

func onPrepare():
	setState(false)


func doCooldownEffect():
	setState(true, true)
	heal()
	var duration = getP_m("dur_blind")
	giveStacksTemporary(opponent(), CoreConst.EventType.Blind, 
		blindAmount, duration)
	particleTimer.stop()
	particleTimer.start(duration)


func onCombatEnd():
	particleTimer.stop()


func onParticleTimeout():
	setState(false)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(active):
	if active:
		pass
	else:
		pass
		

func _readyInit():
	._readyInit()
	particleTimer = newItemTimer("ParticleTimer", "onParticleTimeout", false)
	blindAmount = getP3()
