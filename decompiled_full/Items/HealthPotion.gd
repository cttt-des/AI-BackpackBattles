extends Potion

onready var healthThreshold = getP1() / 100.0

func onTriggerPotion(triggerEvent = null):
	heal(getP_m("heal"), triggerEvent)
	cleansePoison(getP3(), triggerEvent)

func onPrepare():
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDamaged(_healthChange, event):
	if isEmpty(): return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		consumePotion(event)

func getTriggerPriority() -> int:
	return Priority.High
