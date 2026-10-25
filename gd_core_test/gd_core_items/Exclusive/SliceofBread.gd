extends Food
var staminaThreshold
var stamina

func doCooldownEffect():
	if character().getCurrentStamina() < staminaThreshold:
		giveStamina(stamina)
	activate()

func _readyInit():
	._readyInit()
	staminaThreshold = getP("staminat")
	stamina = getP("stamina")
