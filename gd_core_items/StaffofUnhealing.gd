extends Item
var buffActive = false
var activationParticles
var unhealingTimer
var manaCost

func onPrepare():
	setState(false)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		var healAmount = getP_m("heal")
		if character().getMana() >= manaCost:
			if not buffActive:
				setState(true, true)
				character().giveUnhealing(1.0)
			unhealingTimer.start(getP_m("dur_unhealing"))
			var event = useMana(manaCost)
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
		pass
	else:
		pass
	
	buffActive = active

func _readyInit():
	._readyInit()
	unhealingTimer = newItemTimer("UnhealingTimer", "buffEnded", false)
	manaCost = getP2()
