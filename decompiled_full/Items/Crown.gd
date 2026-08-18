extends Item

const activationPulse = preload("res://Items/Animations/BookOfLightActivationPulse.tscn")

onready var activationParticles = $ActivationParticles
onready var buffTimer = $BuffTimer
onready var manaCost = getP("mana")
onready var light = $Icon / CircleLight

enum CrownState{
	Inactive, 
	Active, 
	Used
}

var crownState: int

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
		Util.createPulse(activationPulse, self, global_position)
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
		activationParticles.deactivate()
		light.self_modulate = Color.white
		light.show()
	
	elif _crownState == CrownState.Active:
		activationParticles.activate()
		light.self_modulate = Color(1.3, 1.3, 1.3, 1)
		light.show()
	
	else:
		activationParticles.deactivate()
		light.hide()
	
	crownState = _crownState
