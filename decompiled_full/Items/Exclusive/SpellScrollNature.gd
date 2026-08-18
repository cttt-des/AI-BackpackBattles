extends Item

onready var staminaNeeded: = getP("staminat")
onready var stamina: = getP("stamina")
onready var manaNeeded: = getP("mana")

var staminaAcc: float

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
