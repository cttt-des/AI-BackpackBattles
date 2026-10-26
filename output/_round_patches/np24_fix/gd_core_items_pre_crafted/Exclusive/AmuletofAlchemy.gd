extends Item
const amuletColor = Color(0.266667, 0.309804, 0.960784)
var potionsToTrigger = []
var potionTriggerTimer
var delay

func canAffect(item):
	return item.hasType(CoreConst.Type.Potion)


func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "potion_emptied", "onPotionEmptied")


func onCombatStart():
	giveRandomBuffs(getP("buffs"))
	activate()


func onPotionEmptied(potion):
	if rollChance():
		potionsToTrigger.push_back(potion)
		potionTriggerTimer.start(delay)


func triggerNextPotion():
	var potion = potionsToTrigger.pop_front()
	potion.triggerPotion()
	potion.miniActivate()
	activate()


func onCombatEnd():
	potionTriggerTimer.stop()
	potionsToTrigger.clear()

func _readyInit():
	._readyInit()
	potionTriggerTimer = newItemTimer("PotionTriggerTimer", "triggerNextPotion", true)
	delay = getP("delay")
	pass

