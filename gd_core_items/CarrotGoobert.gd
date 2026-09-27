extends Goobert
var empower
var particleTimer
var activationParticles

func onPrepare():
	setState(false)


func doCooldownEffect():
	setState(true, true)
	cleanseRandomDebuffs(getP2())
	var duration = getP_m("dur")
	giveStacksTemporary(character(), CoreConst.EventType.Empower, 
		empower, duration)
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
	empower = getP3()
	particleTimer = newItemTimer("ParticleTimer", "onParticleTimeout", false)
