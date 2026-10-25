extends Item
class_name Potion
export var potionColor: Color
var fluidTween
var isFull: bool = true
var connector = null
var fluid
var fluidGradientTex
var fluidGradient
var baseFoaminess
var baseScroll
var baseLevel

func prepare():
	.prepare()
	setState(true)


func canAffect(item):
	return item.hasType(CoreConst.Type.Potion)


func isEmpty():
	return not isFull


func fill():
	isFull = true


func empty():
	isFull = false


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
	ctx.bus.emitSignal(self, "potion_triggered", [self])


func onStateChanged(_isFull):
	if _isFull:
		fill()
	else:
		empty()
	
	isFull = _isFull


func activate(damageRes = null, playCombatAni = true, consume = false, 
	animationOverride = null, emitSignal: bool = true):
	
	.activate(damageRes, playCombatAni, consume, null)
	
	if emitSignal:
		ctx.bus.emitSignal(self, "potion_emptied", [self])


func shopEntered(craft: bool):
	.shopEntered(craft)
	if not isFull:
		fill()


func getAffectedCellsAfterRotate_primary(rotatedCells) -> Array:
	
	
	
	
	if faceDirection == CoreConst.FaceDirection.DOWN:
		return [rotatedCells[1] + Vector2.UP]
	else:
		return [rotatedCells[0] + Vector2.UP]


func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	.addToInventory(_inventory, _occupiedCells, _placedByPlayer)
	updateConnector()


func onRemoveFromInventory():
	resetGradient()


func onFusingAsIngredient():
	resetGradient()


func onAffectedItemAdded(item, color: int):
	if color == CoreConst.Affected.Primary:
		updateConnector()


func onAffectedItemRemoved(item, color: int):
	if color == CoreConst.Affected.Primary:
		updateConnector()


func updateConnector():
	pass

func resetGradient():
	pass


func discard(discardGems = true):
	if pooled:
		resetGradient()
	.discard(discardGems)


func getStarPosition() -> Vector2:
	return Vector2.ZERO

func _readyInit():
	._readyInit()
	pass
		
	



