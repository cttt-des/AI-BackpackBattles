extends Item

onready var speedTimer: = $SpeedTimer
onready var healthThreshold: = getP("healtht") / 100.0 - 0.0001
onready var manaNeeded: = int(getP("manat"))
onready var luck: = int(getP("luck"))
onready var empower: = int(getP("empower"))
onready var bonusSpeed: = getP("speed") / 100.0
var hasActivated: bool

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
	return Priority.High + 2

func onSpeedTimerTimeout():
	for item in getAffectedItems():
		item.reduceSpeed(bonusSpeed)

func onCombatEnd():
	speedTimer.stop()
