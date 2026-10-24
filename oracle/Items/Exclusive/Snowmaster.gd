extends Item

onready var iceSpeed = getP("speed") / 100.0
onready var cold: = int(getP("cold"))
onready var empower: = int(getP("empower"))
onready var coldNeeded: = int(getP("coldt"))

func canAffect(item):
	return item.hasType(Type.Ice)

func onPrepare():
	addSpeed(getNumAffectedItems() * iceSpeed)

func doCooldownEffect():
	if opponent().getCold() >= coldNeeded:
		giveEmpower(empower)
	else:
		inflictCold(cold)
	
	cleanseRandomDebuffs(1)
	
	activate()
