extends Potion
var debuffsNeeded: int

func onPrepare():
	connectToCharacterDebuffs("debuffsChanged")


func debuffsChanged(_amount, event):
	if isEmpty(): return
	
	if character().getDebuffStacks() >= debuffsNeeded:
		consumePotion()


func onTriggerPotion(triggerEvent = null):
	cleanseRandomDebuffs(getP2())

func _readyInit():
	._readyInit()
	debuffsNeeded = getP1()
