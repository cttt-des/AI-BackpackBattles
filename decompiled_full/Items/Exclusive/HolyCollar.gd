extends RangerCollar

onready var luck: = int(getP("luck"))
onready var regen: = int(getP("regen"))

func canAffect(item):
	return item.canActivate()

func onPrepare():
	for item in affectedItems:
		connectForCombat(item, "activated", "onItemActivated")
	
	if not affectedItems.empty():
		connectForCombat(character(), "character_lucky_changed", "onLuckyOrRegenChanged")
		connectForCombat(character(), "character_regeneration_changed", "onLuckyOrRegenChanged")

func onLuckyOrRegenChanged(amount, _event):
	for item in affectedItems:
		item.changeCritChancePercent(amount * getChance2())

func onItemActivated(event):
	if rollChance():
		giveLucky(luck, event)
		giveRegeneration(regen, event)
		miniActivate()
