extends Potion

func onTriggerPotion(triggerEvent = null):
	inflictPoison(getP1(), triggerEvent)
	selfInflictPoison(getP2(), triggerEvent)

func onPrepare():
	connectForCombat(opponent(), "character_healed", "onOpponentHeal")

func onOpponentHeal(_amount, event):
	if isEmpty(): return
	
	drink()
	
	triggerPotion(event)
	
	var affected = getAffectedItems()
	if not affected.empty():
		affected[0].triggerPotion(event)
		affected[0].miniActivate()
	
	activate()

