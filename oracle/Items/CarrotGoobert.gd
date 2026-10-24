extends Goobert

onready var empower = getP3()

onready var particleTimer = $ParticleTimer
onready var activationParticles = $EmpowerParticles

func onPrepare():
	setState(false)
	activationParticles.global_rotation = 0

func doCooldownEffect():
	setState(true, true)
	cleanseRandomDebuffs(getP2())
	var duration = getP_m("dur")
	giveStacksTemporary(character(), Game.EventType.Empower, 
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
		activationParticles.activate()
	else:
		activationParticles.deactivate()
