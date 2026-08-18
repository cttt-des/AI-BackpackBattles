extends Item

onready var moonArmorDescriptor = ItemBook.getDescriptor("Moon Armor")
onready var moonShieldDescriptor = ItemBook.getDescriptor("Moon Shield")
onready var manaOrbDescriptor = ItemBook.getDescriptor("Mana Orb")
onready var timeAdvance: = getP("time")
onready var blind: = int(getP("blind"))
var boosted: = 0

func canAffect(item):
	return item.isA(moonArmorDescriptor) or item.isA(moonShieldDescriptor)

func getData():
	return boosted

func setData(data):
	if data != null:
		boosted = data

func onBought():
	boosted = 1

func onPostCombatStart():
	Game.combatSceneNode.advanceTime(timeAdvance)

func onPrepare():
	connectForCombat(Game.combatTimer, "fatigue_start", "onFatigueStarted")
	
	for item in getAffectedItems():
		if item.isA(moonArmorDescriptor):
	
			connectForCombat(item, "activated", "onMoonArmorActivated")
		else:
	
			connectForCombat(item, "activated", "onMoonShiedActivated")

func onFatigueStarted():
	var bonusHealth = getP_m("maxhealth") / 100.0 * character().getMaxHealth()
	giveMaxHealth(bonusHealth)
	activate()

func onMoonArmorActivated(event):
	inflictBlind(blind, event)

func onMoonShiedActivated(event):
	giveReflectStacks(1)

func onItemRoll(descr):
	if descr == manaOrbDescriptor and boosted > 0:
		ItemBook.multiplyWeight(1.5)

func onItemRolled(descr):
	if descr == manaOrbDescriptor:
		boosted -= 1
