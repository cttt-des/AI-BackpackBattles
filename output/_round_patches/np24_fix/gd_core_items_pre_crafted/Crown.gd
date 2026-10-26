extends Item
enum CrownState{
	Inactive, 
	Active, 
	Used
}
var crownState: int
var activationParticles
var buffTimer
var manaCost
var light

func onPrepare():
	setState(CrownState.Inactive)
	connectForCombat(character(), "character_mana_changed", "checkTrigger")
	connectForCombat(character(), "character_invulnerable_end", "onInvuEnded")


func onInvuEnded(triggerEvent):
	checkTrigger(0, triggerEvent)


func checkTrigger(_amount, triggerEvent):
	if (crownState == CrownState.Inactive and 
		character().isVulnerable() and 
		checkMana(manaCost)):
		
		setState(CrownState.Active, true)
		var invuDur = getP_m("dur_invu")
		var event = character().makeInvulnerable(invuDur, self, triggerEvent)
		buffTimer.start(invuDur)
		useMana(manaCost, event)
		activate()


func buffEnded():
	setState(CrownState.Used, true)


func doCooldownEffect():
	cleanseBlind(1)
	heal()
	activate()


func onCombatEnd():
	buffTimer.stop()


func onShopEntered():
	onStateChanged(CrownState.Inactive)


func onStateChanged(_crownState):
	if _crownState == CrownState.Inactive:
		pass
	
	elif _crownState == CrownState.Active:
		pass
	
	else:
		pass
	
	crownState = _crownState

func _readyInit():
	._readyInit()
	buffTimer = newItemTimer("BuffTimer", "buffEnded", false)
	manaCost = getP("mana")
