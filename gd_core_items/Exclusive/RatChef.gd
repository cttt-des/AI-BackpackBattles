extends "res://gd_core_items/Exclusive/Rat.gd"
var stamina
var empower

func initRat():
	pass


func onCombatStart():
	var numAffectedFood = 0
	for item in getAffectedItems():
		if item.hasType(CoreConst.Type.Food):
			numAffectedFood += 1
	
	giveRegeneration(numAffectedFood)


func doCooldownEffect():
	giveStamina(stamina)
	giveEmpower(empower)
	activate()


func getCraftingOffset(forDirection):
	match forDirection:
		CoreConst.FaceDirection.UP:
			return Vector2(0, - 1)
		CoreConst.FaceDirection.DOWN:
			return Vector2(1, 0)
		CoreConst.FaceDirection.LEFT:
			return Vector2( - 1, 1)
		CoreConst.FaceDirection.RIGHT:
			return Vector2(0, 0)

func _readyInit():
	._readyInit()
	stamina = getP("stamina")
	empower = getP("empower")
