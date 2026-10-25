extends Item
var staminaAcc: float
var staminaNeeded
var stamina
var manaNeeded

func canAffect(item):
	return item.canUseStamina()


func onPrepare():
	staminaAcc = 0.0
	for item in getAffectedItems():
		connectForCombat(item, "used_stamina", "onItemUsedStamina")


func onItemUsedStamina(amount):
	staminaAcc += amount
	var activating = false
	
	while staminaAcc >= staminaNeeded - 0.0001:
		if character().getMana() >= manaNeeded:
			var event = useMana(manaNeeded)
			giveStamina(stamina, event)
			activate()
			activating = true
		staminaAcc -= staminaNeeded
	
	showCooldownSmooth(staminaAcc / staminaNeeded, activating)

func _readyInit():
	._readyInit()
	staminaNeeded = getP("staminat")
	stamina = getP("stamina")
	manaNeeded = getP("mana")
