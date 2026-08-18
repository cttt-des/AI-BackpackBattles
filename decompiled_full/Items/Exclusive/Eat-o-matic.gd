extends Item

onready var foodSpeed: = getP("speed") / 100.0
onready var chargedSpeed: = getP("speed2") / 100.0
onready var otherSpeed: = getP("speed3") / 100.0
onready var arm = $Icon / Arm
onready var armAnimation = $Icon / AnimationPlayer

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

func canAffect(item):
	return item.hasType(Type.Food)

func canAffect_global(item):
	if not item.hasType(Type.Food): return false
	if item in currentAffectedItems[Affected.Primary]:
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
	
	arm.deactivate()

func combatStart():
	.combatStart()
	arm.z_index = 4
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
	arm.z_index = 0

func stopArmAni():
	arm.activate()

func onStateChanged(_armState: int):
	armState = _armState
	if armState == ArmState.Off:
		
		if armAnimation.current_animation != "":
			armAnimation.stop()
			arm.rotation += 2 * PI
			var angleDif = arm.rotation
			var dur = angleDif * 0.3
			
			armTween = Util.refreshTween(armTween)
			armTween.tween_property(arm, "rotation", 
				0.0, dur).set_ease(Tween.EASE_OUT)
			armTween.tween_callback(self, "stopArmAni")
	else:
		arm.deactivate()
		armAnimation.play("Spin")
		
		armTween = Util.refreshTween(armTween)
		if armState == ArmState.Slow:
			armTween.tween_property(armAnimation, "playback_speed", 
				SLOW_SPEED, 0.5)
		else:
			armTween.tween_property(armAnimation, "playback_speed", 
				FAST_SPEED, 0.2)
		


