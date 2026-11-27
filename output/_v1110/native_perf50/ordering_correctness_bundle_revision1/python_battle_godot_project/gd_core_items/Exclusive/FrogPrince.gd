extends "res://gd_core_items/Exclusive/Toad.gd"
enum FrogState{
	Inactive, 
	Active, 
	Used
}
var frogState: int
var activationParticles
var buffTimer
var light
var blind

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
		pass
	
	elif _frogState == FrogState.Active:
		pass
	
	else:
		pass
	
	frogState = _frogState

func _readyInit():
	._readyInit()
	buffTimer = newItemTimer("BuffTimer", "buffEnded", false)
	blind = int(getP("blind"))
