extends Item
class_name DragonEgg

export (PackedScene) var hatchParticles
export (PackedScene) var firePulse
export var hatchSound = preload("res://Assets/Sound/IceCracking1.wav")
export (String) var whelpName

var roundsToHatch
var reflectionStacks

func _ready() -> void :
	roundsToHatch = getP2()
	updateEgg()

func getData():
	return roundsToHatch

func setData(data):
	roundsToHatch = data
	updateEgg()

func updateEgg():
	if canHatch():
		showCooldownSmooth(1.0, false)
	else:
		showCooldownSmooth(1.0 - roundsToHatch / getP2(), false)

func isNextToNest():
	if placed:
		for item in inventory.getItems():
			if item.getName() == "Dragon Nest":
				return self in item.getAffectedItems()
		
	return false

func readyToTransform() -> bool:
	return canHatch()

func canHatch():
	return (roundsToHatch == 0 or 
			(roundsToHatch == 1 and isNextToNest()))

func shopEntered(craft: bool):
	.shopEntered(craft)
	
	if CustomRules.isSwitchMode():
		showCooldownSmooth(1.0, false)
		startHatching()
		return
	
	
	
	if (craft and 
		bondedBaseItem != null and 
		not bondedBaseItem.isCatalystBond(self)):
		return
	
	roundsToHatch -= 1
	updateEgg()
	if canHatch():
		startHatching()

func startHatching():
	Util.callDelayed(self, "hatch", TRANSFORMATION_DUR - 0.1)
	sprite.position = Vector2(0, 69)
	sprite.offset = Vector2(0, - 138)
	for shadow in shadows:
		shadow.offset = Vector2(0, - 138)
	animation.play("Hatch")

func hatch():
	call_deferred("hatch_deferred")

func hatch_deferred():
	inventory.replaceItem(self, ItemBook.generateItem(whelpName))
	var particles = hatchParticles.instance()
	get_parent().add_child(particles)
	particles.global_position = global_position
	particles.restart()
	Util.createPulse(firePulse, self, global_position)
	Sound.playSound(hatchSound)
	Game.saveRunState()
	
