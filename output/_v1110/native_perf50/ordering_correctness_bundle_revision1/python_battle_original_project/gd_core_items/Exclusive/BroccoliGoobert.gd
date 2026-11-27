extends Goobert
var luck
var luckNeeded
var regen

func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		giveRegeneration(regen)
	else:
		giveLucky(luck)

func _readyInit():
	._readyInit()
	luck = int(getP("luck"))
	luckNeeded = int(getP("luckt"))
	regen = int(getP("regen"))
