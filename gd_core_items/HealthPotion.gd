extends Potion
var healthThreshold

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
	return CoreConst.Priority.High

func _readyInit():
	._readyInit()
	healthThreshold = getP1() / 100.0
