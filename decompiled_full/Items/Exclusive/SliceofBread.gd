extends Food

onready var staminaThreshold: = getP("staminat")
onready var stamina: = getP("stamina")

func doCooldownEffect():
	if character().getCurrentStamina() < staminaThreshold:
		giveStamina(stamina)
	activate()
