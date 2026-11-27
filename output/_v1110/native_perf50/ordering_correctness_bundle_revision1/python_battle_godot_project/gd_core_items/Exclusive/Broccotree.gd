extends Food
var staminaPerRegen: float
var luck
var luckNeeded
var regen

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

func _readyInit():
	._readyInit()
	luck = int(getP("luck"))
	luckNeeded = int(getP("luckt"))
	regen = int(getP("regen"))
