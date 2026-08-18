extends Item

onready var healthThreshold: = getP1() / 100.0 - 0.0001
var hasActivated: bool

func onPrepare():
	hasActivated = false
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		giveLucky(getP2(), event)
		giveEmpower(getP3(), event)
		giveBlock(getBlock(), true, event)
		consume()

func getTriggerPriority() -> int:
	return Priority.High + 2
