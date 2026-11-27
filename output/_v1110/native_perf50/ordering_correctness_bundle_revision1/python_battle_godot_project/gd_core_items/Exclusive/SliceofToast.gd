extends Food
var staminaThreshold
var stamina
var regen

func doCooldownEffect():
	if character().getCurrentStamina() < staminaThreshold:
		giveStamina(stamina)
	else:
		giveRegeneration(regen)
	activate()

func _readyInit():
	._readyInit()
	staminaThreshold = getP("staminat")
	stamina = getP("stamina")
	regen = int(getP("regen"))
