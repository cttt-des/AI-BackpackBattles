extends Weapon
var buffed = false
var buffParticles
var empowerNeeded
var buffedStamina
var buffedCooldown

func isBuffed():
	return buffed
	


func getStaminaCost() -> float:
	var override = statDisplayOverrides[CoreConst.ItemStat.StaminaCost]
	if override: return override
	
	if isBuffed():
		return buffedStamina * staminaFactor
	else:
		return .getStaminaCost()


func onPrepare():
	setState(false)
	connectForCombat(character(), "character_empower_changed", "empowerChanged")


func empowerChanged(amount, event):
	if not buffed and character().getEmpower() >= empowerNeeded:
		setState(true)
		setBaseCooldown(buffedCooldown)
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.StaminaCost)
	
	elif buffed and character().getEmpower() < empowerNeeded:
		setState(false)
		resetBaseCooldown()
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.StaminaCost)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(_buffed):
	buffed = _buffed
	if buffed:
		pass
	else:
		pass
		

func _readyInit():
	._readyInit()
	empowerNeeded = int(getP1())
	buffedStamina = getP2()
	buffedCooldown = getP3()
