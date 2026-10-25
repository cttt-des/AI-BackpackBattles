extends Item
var empower
var regen
var speed_v

func isAffectingDistinct(color = CoreConst.Affected.Primary) -> bool:
	return color == CoreConst.Affected.Primary


func canAffect(item):
	return item.isClassItem()


func onPrepare():
	addSpeed(speed_v * getNumDistinctAffectedItems())


func doCooldownEffect():
	var curEmpower = character().getEmpower()
	var curRegen = character().getRegeneration()
	
	if curRegen < curEmpower:
		giveRegeneration(regen)
	elif curRegen > curEmpower:
		giveEmpower(empower)
	else:
		if ctx.util.flip():
			giveRegeneration(regen)
		else:
			giveEmpower(empower)
	
	activate()


func onItemRoll(descr):
	pass

func _readyInit():
	._readyInit()
	empower = int(getP("empower"))
	regen = int(getP("regen"))
	speed_v = int(getP("speed")) / 100.0
