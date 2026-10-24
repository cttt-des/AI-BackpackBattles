extends Goobert

const activationPulse = preload("res://Items/Animations/SmallBlindPulse.tscn")

onready var particleTimer = $ParticleTimer
onready var activationParticles = $ActivationParticles
onready var blindAmount = getP3()

func onPrepare():
	setState(false)

func doCooldownEffect():
	setState(true, true)
	heal()
	var duration = getP_m("dur_blind")
	giveStacksTemporary(opponent(), Game.EventType.Blind, 
		blindAmount, duration)
	particleTimer.stop()
	particleTimer.start(duration)
	Util.createPulse(activationPulse, self, global_position)

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
		
