extends Item

onready var healthThreshold = getP("healtht") / 100.0 - 0.0001
onready var empower: = int(getP("empower"))
onready var debuffs: = int(getP("cleanse"))
onready var dodges: = int(getP("dodge"))

var hasActivated: bool

func onPrepare():
	hasActivated = false
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		giveEmpower(empower, event)
		cleanseRandomDebuffs(debuffs)
		character().changeDodgeStacks(dodges)
		consume()

func getTriggerPriority() -> int:
	return Priority.High + 2
