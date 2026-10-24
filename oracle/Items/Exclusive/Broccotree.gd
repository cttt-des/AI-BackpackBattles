extends Food

onready var luck: = int(getP("luck"))
onready var luckNeeded: = int(getP("luckt"))
onready var regen: = int(getP("regen"))
var staminaPerRegen: float

func doCooldownEffect():
	giveLucky(luck)
	
	if character().getLucky() >= luckNeeded:
		giveRegeneration(regen)
	
	activate()

func onPrepare():
	var baseStaminaRegen = character().baseStaminaRegen
	staminaPerRegen = getP("stamina") * baseStaminaRegen / 100.0
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")

func onRegenChanged(amount, event):
	if amount > 0:
		character().giveStaminaRegeneration(amount * staminaPerRegen)

