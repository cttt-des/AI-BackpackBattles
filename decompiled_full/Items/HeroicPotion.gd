extends Potion

func onTriggerPotion(triggerEvent = null):
	giveStamina(getP1(), triggerEvent)
	giveEmpower(getP2(), triggerEvent)

func onPrepare():
	connectForCombat(character(), "character_pre_use_stamina", "checkStamina")

func checkStamina(amount):
	if isEmpty(): return
	
	if character().getCurrentStamina() < amount:
		consumePotion()
