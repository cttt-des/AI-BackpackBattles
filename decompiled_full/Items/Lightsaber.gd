extends Weapon

const activationPulse = preload("res://Items/Animations/BlindPulse.tscn")

onready var blindingLightTimer = $BlindingLightTimer
onready var activationParticles = $ActivationParticles
onready var regenNeeded: = int(getP("regent"))

onready var blind: = int(getP("blind"))
onready var damPerBlind = getP("dam_blind")

func onPrepare():
	setState(false)
	connectForCombat(character(), "blinding_light_ended", "onBlindingLightEnded")
	connectForCombat(opponent(), "character_blind_changed", "onOpponentBlindChanged")
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")

func inflict(duration, event):
	giveStacksTemporary(opponent(), Game.EventType.Blind, 
			blind, duration, event)

func onRegenChanged(amount, triggerEvent):
	if amount < 0: return
	
	if not character().blindingLightActive and character().getRegeneration() >= regenNeeded:
		
		setState(true, true)
		character().startBlindingLight()
		var event = useRegeneration(regenNeeded, triggerEvent)
		var duration = getP_m("dur_blind")
		inflict(duration, event)
		Util.createPulse(activationPulse, self, global_position)
		
		activate(null, false)
		blindingLightTimer.start(duration)

func onOpponentBlindChanged(amount, event):
	changeVaryingDamage(damPerBlind * amount)

func onCombatEnd():
	blindingLightTimer.stop()
	
func onBlindingLightTimeout():
	setState(false)
	
	
	Util.callNextFrame(character(), "endBlindingLight")

func onBlindingLightEnded(event):
	onRegenChanged(0, event)
	

func onShopEntered():
	onStateChanged(false)

func onStateChanged(active):
	if active:
		activationParticles.activate()
	else:
		activationParticles.deactivate()
