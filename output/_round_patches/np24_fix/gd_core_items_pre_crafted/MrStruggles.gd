extends Item
const plushies = ["Mrs Struggles", "Miss Fortune"]
var hasActivated: bool
var speedbuffTimer
var activationParticles
var healthThreshold
var bonusSpeed
var fatigueDam
var speedBuffParticles1
var speedBuffParticles2

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	for debuff in CoreConst.getDebuffs():
		connectForCombat(character(), character().buffs[debuff].signalName, 
		"onDebuffed")
	
	
	hasActivated = false
	setState(false)
	connectForCombat(character(), "character_damaged", "onDamaged")


func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		setState(true)
		for item in getAffectedItems():
			item.addSpeed(bonusSpeed)
		speedbuffTimer.start(getP_m("dur_speed"))
	

func onSpeedbuffTimeout():
	setState(false)
	for item in getAffectedItems():
		item.reduceSpeed(bonusSpeed)


func onDebuffed(amount, event):
	if checkTriggerCount(10):
		if rollChance():
			var debuffType = event.type
			var dur = event.getParam("duration", - 1)
			giveStacksTemporary(opponent(), debuffType, amount, dur, event)
				


func doCooldownEffect():
	inflictFatigueDamage(fatigueDam)
	activate()






func onCombatEnd():
	speedbuffTimer.stop()


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 3


func getDescription(wrapInColor = true) -> String:
	return ""

func rollShopChance(shopChance = descriptor.shopChance) -> bool:
	return false

func getGatedDescriptor(rarity) -> CoreItemData:
	return ctx.item_book.getDescriptor(ctx.util.pickRandomElement(plushies))


func onShopEntered():
	onStateChanged(false)


func onStateChanged(speedBuffActive):
	if speedBuffActive:
		pass
	else:
		pass
	

func _readyInit():
	._readyInit()
	speedbuffTimer = newItemTimer("SpeedbuffTimer", "onSpeedbuffTimeout", false)
	healthThreshold = getP2() / 100.0 - 0.0001
	bonusSpeed = getP3() / 100.0
	fatigueDam = int(getP1())
