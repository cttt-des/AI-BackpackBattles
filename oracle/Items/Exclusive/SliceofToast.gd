extends Food

onready var staminaThreshold: = getP("staminat")
onready var stamina: = getP("stamina")
onready var regen: = int(getP("regen"))

func doCooldownEffect():
	if character().getCurrentStamina() < staminaThreshold:
		giveStamina(stamina)
	else:
		giveRegeneration(regen)
	activate()
