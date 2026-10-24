extends "res://Items/Exclusive/Toad.gd"

const activationPulse = preload("res://Items/Animations/BookOfLightActivationPulse.tscn")

onready var activationParticles = $ActivationParticles
onready var buffTimer = $BuffTimer
onready var light = $Icon / CircleLight

onready var blind: = int(getP("blind"))

enum FrogState{
	Inactive, 
	Active, 
	Used
}

var frogState: int

func onGainThresholdReached(ticks, event):
	cleanseBlind(blind, event)
	heal(ticks * getP_m("heal"), event)
	miniActivate()

func onUseThresholdReached(ticks, event):
	if frogState == FrogState.Inactive:
		setState(FrogState.Active, true)
		giveLucky(luck, event)
		giveMana(mana, event)
		var invuDur = getP_m("dur_1")
		character().makeInvulnerable(invuDur, self, event)
		buffTimer.start(invuDur)
		Util.createPulse(activationPulse, self, global_position)
		miniActivate()

func onPrepare():
	.onPrepare()
	setState(FrogState.Inactive)

func buffEnded():
	setState(FrogState.Used, true)

func onCombatEnd():
	buffTimer.stop()

func onShopEntered():
	onStateChanged(FrogState.Inactive)

func onStateChanged(_frogState):
	if _frogState == FrogState.Inactive:
		activationParticles.deactivate()
		light.self_modulate = Color.white
		light.show()
	
	elif _frogState == FrogState.Active:
		activationParticles.activate()
		light.self_modulate = Color(1.3, 1.3, 1.3, 1)
		light.show()
	
	else:
		activationParticles.deactivate()
		light.hide()
	
	frogState = _frogState
