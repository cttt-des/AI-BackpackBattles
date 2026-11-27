extends Item
var hasActivated: bool
var speedTimer
var healthThreshold
var manaNeeded
var luck
var empower
var bonusSpeed

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	hasActivated = false
	connectForCombat(character(), "character_damaged", "onDamaged")


func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		if character().getMana() >= manaNeeded:
			hasActivated = true
			var event2 = useMana(manaNeeded)
			giveLucky(luck, event2)
			giveEmpower(empower, event2)
			giveBlock(getBlock(), true, event2)
			
			for item in getAffectedItems():
				item.addSpeed(bonusSpeed)
			
			speedTimer.start(getP_m("dur_speed"))
			
			consume()


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 2


func onSpeedTimerTimeout():
	for item in getAffectedItems():
		item.reduceSpeed(bonusSpeed)


func onCombatEnd():
	speedTimer.stop()

func _readyInit():
	._readyInit()
	speedTimer = newItemTimer("SpeedTimer", "onSpeedTimerTimeout", false)
	healthThreshold = getP("healtht") / 100.0 - 0.0001
	manaNeeded = int(getP("manat"))
	luck = int(getP("luck"))
	empower = int(getP("empower"))
	bonusSpeed = getP("speed") / 100.0
