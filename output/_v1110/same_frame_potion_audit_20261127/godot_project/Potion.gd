extends "res://ItemStub.gd"
var isFull = true
func isEmpty():
	return not isFull
func drink():
	setState(false, true)
func consumePotion(event = null, withActivate: bool = true):
	if isEmpty(): return
	
	drink()
	
	triggerPotion(event)
	
	var affected = getAffectedItems()
	if not affected.empty():
		affected[0].triggerPotion()
		affected[0].miniActivate()
	
	if withActivate:
		activate()
func onTriggerPotion(triggerEvent = null):
	pass
func triggerPotion(triggerEvent = null):
	onTriggerPotion(triggerEvent)
	playActivationAnimation()
	EventBus.emitSignal(self, "potion_triggered", [self])
func activate(damageRes = null, playCombatAni = true, consume = false, 
	animationOverride = null, emitSignal: bool = true):
	
	.activate(damageRes, playCombatAni, consume, null)
	
	if emitSignal:
		EventBus.emitSignal(self, "potion_emptied", [self])
