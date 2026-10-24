extends Potion

func onTriggerPotion(triggerEvent = null):
	healthToBlock(getP2(), getBlock(), triggerEvent)

func onPrepare():
	connectForCombat(character(), "character_block_changed", "onBlockChanged")

func onBlockChanged(_amount, event):
	if isEmpty(): return
	
	if character().getBlock() >= getP1():
		
		consumePotion()
