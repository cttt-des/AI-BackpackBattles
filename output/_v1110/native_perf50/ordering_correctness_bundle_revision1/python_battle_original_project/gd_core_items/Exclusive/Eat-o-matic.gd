extends Item
var affectedFood = null
var otherFood: Array
var armTween: SceneTreeTween
const SLOW_SPEED = 0.2
const FAST_SPEED = 1.0
enum ArmState{
	Off, 
	Slow, 
	Fast
}
var armState: int
var foodSpeed
var chargedSpeed
var otherSpeed
var arm
var armAnimation

func canAffect(item):
	return item.hasType(CoreConst.Type.Food)


func canAffect_global(item):
	if not item.hasType(CoreConst.Type.Food): return false
	if item in currentAffectedItems[CoreConst.Affected.Primary]:
		return false
	
	return true


func onPrepare():
	setState(ArmState.Off)
	affectedFood = getFirstAffectedItem()
	if affectedFood != null:
		affectedFood.addSpeed(foodSpeed)
	
	otherFood.clear()
	for item in inventory.getItems():
		if canAffect_global(item) and item != affectedFood:
			otherFood.push_back(item)
	


func combatStart():
	.combatStart()
	if armState != ArmState.Fast:
		setState(ArmState.Slow)


func onChargeReceived(_charge):
	if numCharges == 1:
		setState(ArmState.Fast)
		if affectedFood != null:
			affectedFood.addSpeed(chargedSpeed - foodSpeed)
		for food in otherFood:
			food.addSpeed(otherSpeed)
		

func onChargeLeft(_charge):
	if numCharges == 0:
		setState(ArmState.Slow)
		if affectedFood != null:
			affectedFood.reduceSpeed(chargedSpeed - foodSpeed)
		for food in otherFood:
			food.reduceSpeed(otherSpeed)


func onCombatEnd():
	setState(ArmState.Off)


func onShopEntered():
	onStateChanged(ArmState.Off)


func stopArmAni():
	pass


func onStateChanged(_armState: int):
	armState = _armState
	if armState == ArmState.Off:
		pass
		
			
	else:
		
		if armState == ArmState.Slow:
			pass
		else:
			pass
		


func _readyInit():
	._readyInit()
	foodSpeed = getP("speed") / 100.0
	chargedSpeed = getP("speed2") / 100.0
	otherSpeed = getP("speed3") / 100.0
