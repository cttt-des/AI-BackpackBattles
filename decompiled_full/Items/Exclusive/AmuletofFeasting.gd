extends Item

const amuletColor = Color(0.929412, 0.498039, 0.180392)

onready var foodSpeed = getP("foodspeed") / 100.0

func _ready():
	specificDragParticles[0].self_modulate = amuletColor

func canAffect(item):
	return item.hasType(Type.Food)

func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(foodSpeed)

func getReplaceDescriptor(rarity) -> ItemDescriptor:
	return ItemBook.getFoodOfRarity(rarity)

func getRelatedItems():
	var food = []
	for rarity in range(Rarity.Common, Rarity.Godly + 1):
		food.append_array(ItemBook.foodsForRarity[rarity])
	return food

func getRelatedItemColumns() -> int:
	return 4
