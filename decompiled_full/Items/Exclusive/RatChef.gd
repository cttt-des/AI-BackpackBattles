extends "res://Items/Exclusive/Rat.gd"

onready var stamina: = getP("stamina")
onready var empower: = getP("empower")

func initRat():
	pass

func onCombatStart():
	var numAffectedFood = 0
	for item in getAffectedItems():
		if item.hasType(Type.Food):
			numAffectedFood += 1
	
	giveRegeneration(numAffectedFood)

func doCooldownEffect():
	giveStamina(stamina)
	giveEmpower(empower)
	activate()

func getCraftingOffset(forDirection):
	match forDirection:
		FaceDirection.UP:
			return Vector2(0, - 1)
		FaceDirection.DOWN:
			return Vector2(1, 0)
		FaceDirection.LEFT:
			return Vector2( - 1, 1)
		FaceDirection.RIGHT:
			return Vector2(0, 0)
