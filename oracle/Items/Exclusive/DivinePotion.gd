extends Potion

onready var debuffsNeeded: int = getP1()

func onPrepare():
	connectToCharacterDebuffs("debuffsChanged")

func debuffsChanged(_amount, event):
	if isEmpty(): return
	
	if character().getDebuffStacks() >= debuffsNeeded:
		consumePotion()

func onTriggerPotion(triggerEvent = null):
	cleanseRandomDebuffs(getP2())

