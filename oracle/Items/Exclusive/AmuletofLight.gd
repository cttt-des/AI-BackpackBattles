extends Item

onready var regenOnActivate: = int(getP("regen"))

const amuletColor = Color(1, 0.850098, 0.400391)

func _ready():
	specificDragParticles[0].self_modulate = amuletColor

func canAffect(item):
	return item.canActivate()

func onPrepare():
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")
	
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")

func onItemActivated(event):
	if event.origin.hasType(Type.Holy):
		if rollChance2():
			giveRegeneration(regenOnActivate, event)
			miniActivate()
	else:
		if rollChance():
			giveRegeneration(regenOnActivate, event)
			miniActivate()

func onRegenChanged(amount, event):
	if amount > 0:
		giveMaxHealth(amount * getP_m("maxhealth"), event)
