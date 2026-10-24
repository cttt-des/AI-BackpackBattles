extends Item

onready var goobertAnimation = $Icon / GoobertAnimation
onready var regen: = int(getP("regen"))
onready var regenNeeded: = int(getP("regent"))
onready var empower: = int(getP("empower"))


func canAffect(item):
	return item.canActivate()

func canAffect_secondary(item):
	return item.canActivate()

func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated1")
	
	for item in getAffectedItems(Affected.Secondary):
		connectForCombat(item, "activated", "onItemActivated2")

func onItemActivated1(event):
	if rollChance():
		giveRegeneration(regen, event)
		miniActivate()

func onItemActivated2(event):
	if character().getRegeneration() >= regenNeeded:
		if rollChance2():
			var event2 = useRegeneration(regenNeeded, event)
			giveEmpower(empower, event2)
			miniActivate()


func doCooldownEffect():
	giveRegeneration(regen)
	if character().getRegeneration() >= regenNeeded:
		var event2 = useRegeneration(regenNeeded)
		giveEmpower(empower, event2)
	activate()










