extends Food

onready var luck: = int(getP("luck"))
onready var luckNeeded: = int(getP("luckt"))
onready var regen: = int(getP("regen"))

func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		giveRegeneration(regen)
	else:
		giveLucky(luck)
	activate()
