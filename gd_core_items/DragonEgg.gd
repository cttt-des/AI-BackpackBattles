extends Item
class_name DragonEgg
export (PackedScene) var hatchParticles
export (PackedScene) var firePulse
export (String) var whelpName
var roundsToHatch
var reflectionStacks

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

func startHatching():
	ctx.util.callDelayed(self, "hatch", TRANSFORMATION_DUR - 0.1)
	for shadow in shadows:
		shadow.offset = Vector2(0, - 138)


func hatch():
	call_deferred("hatch_deferred")


func hatch_deferred():
	pass

func _readyInit():
	._readyInit()
	roundsToHatch = getP2()
	updateEgg()

