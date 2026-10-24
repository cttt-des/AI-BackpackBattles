extends Item

const activationPulse = preload("res://Items/Animations/UnhealingActivationPulse.tscn")

onready var activationParticles = $ActivationParticles
onready var unhealingTimer = $UnhealingTimer
onready var manaCost = getP2()

var buffActive = false

func onPrepare():
	setState(false)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		var healAmount = getP_m("heal")
		if character().getMana() >= manaCost:
			if not buffActive:
				setState(true, true)
				character().giveUnhealing(1.0)
			unhealingTimer.start(getP_m("dur_unhealing"))
			var event = useMana(manaCost)
			Util.createPulse(activationPulse, self, $Icon / PulsePosition.global_position)
			heal(healAmount, event)
		else:
			heal(healAmount)
		
		activate()

func buffEnded():
	character().reduceUnhealing(1.0)
	setState(false)

func onCombatEnd():
	unhealingTimer.stop()

func onShopEntered():
	onStateChanged(false)

func onStateChanged(active):
	if active:
		activationParticles.activate()
	else:
		activationParticles.deactivate()
	
	buffActive = active
