extends Item
var boosted: = 0
var moonArmorDescriptor
var moonShieldDescriptor
var manaOrbDescriptor
var timeAdvance
var blind

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
	ctx.combat.advanceTime(timeAdvance)


func onPrepare():
	connectForCombat(ctx.combat, "fatigue_start", "onFatigueStarted")
	
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
	pass

func onItemRolled(descr):
	if descr == manaOrbDescriptor:
		boosted -= 1

func _readyInit():
	._readyInit()
	moonArmorDescriptor = ctx.item_book.getDescriptor("Moon Armor")
	moonShieldDescriptor = ctx.item_book.getDescriptor("Moon Shield")
	manaOrbDescriptor = ctx.item_book.getDescriptor("Mana Orb")
	timeAdvance = getP("time")
	blind = int(getP("blind"))
