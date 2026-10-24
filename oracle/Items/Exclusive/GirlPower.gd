extends Item

onready var empower: = int(getP("empower"))
onready var regen: = int(getP("regen"))
onready var speed: = int(getP("speed")) / 100.0

func isAffectingDistinct(color = Affected.Primary) -> bool:
	return color == Affected.Primary

func canAffect(item):
	return item.isClassItem()

func onPrepare():
	addSpeed(speed * getNumDistinctAffectedItems())

func doCooldownEffect():
	var curEmpower = character().getEmpower()
	var curRegen = character().getRegeneration()
	
	if curRegen < curEmpower:
		giveRegeneration(regen)
	elif curRegen > curEmpower:
		giveEmpower(empower)
	else:
		if Util.flip():
			giveRegeneration(regen)
		else:
			giveEmpower(empower)
	
	activate()

func onItemRoll(descr):
	if descr.isClassItem():
		ItemBook.multiplyWeight(1.2)
