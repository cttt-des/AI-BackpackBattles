extends Weapon
var blindingLightTimer
var activationParticles
var regenNeeded
var blind
var damPerBlind

func onPrepare():
	setState(false)
	connectForCombat(character(), "blinding_light_ended", "onBlindingLightEnded")
	connectForCombat(opponent(), "character_blind_changed", "onOpponentBlindChanged")
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")


func inflict(duration, event):
	giveStacksTemporary(opponent(), CoreConst.EventType.Blind, 
			blind, duration, event)


func onRegenChanged(amount, triggerEvent):
	if amount < 0: return
	
	if not character().blindingLightActive and character().getRegeneration() >= regenNeeded:
		
		setState(true, true)
		character().startBlindingLight()
		var event = useRegeneration(regenNeeded, triggerEvent)
		var duration = getP_m("dur_blind")
		inflict(duration, event)
		
		activate(null, false)
		blindingLightTimer.start(duration)


func onOpponentBlindChanged(amount, event):
	changeVaryingDamage(damPerBlind * amount)


func onCombatEnd():
	blindingLightTimer.stop()
	

func onBlindingLightTimeout():
	setState(false)
	
	
	ctx.util.callNextFrame(character(), "endBlindingLight")


func onBlindingLightEnded(event):
	onRegenChanged(0, event)
	


func onShopEntered():
	onStateChanged(false)


func onStateChanged(active):
	if active:
		pass
	else:
		pass

func _readyInit():
	._readyInit()
	blindingLightTimer = newItemTimer("BlindingLightTimer", "onBlindingLightTimeout", false)
	regenNeeded = int(getP("regent"))
	blind = int(getP("blind"))
	damPerBlind = getP("dam_blind")
