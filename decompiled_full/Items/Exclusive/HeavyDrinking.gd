extends Item

const activationParticles = preload("res://Items/Exclusive/Particles/HeavyDrinkingActivationParticles.tscn")
onready var potionSpeed: = getP("speed") / 100.0

var allPotions = []
var boostedPotions: = 0

func getData():
	return boostedPotions

func setData(data):
	if data != null:
		boostedPotions = data

func onBought():
	boostedPotions = 3

func isAffectingDistinct(color = Affected.Primary) -> bool:
	return color == Affected.Primary

func canAffect(item):
	return item.hasType(Type.Potion)

func canAffect_global(item):
	return item.hasType(Type.Potion)

func onPrepare():
	addSpeed(getNumDistinctAffectedItems() * potionSpeed)
	
	allPotions.clear()
	for item in inventory.getItems():
		if item.hasType(Type.Potion) and item != self:
			allPotions.push_back(item)

func doCooldownEffect():
	if not allPotions.empty():
		var potionToTrigger = Util.pickRandomElement(allPotions)
		potionToTrigger.triggerPotion()
		potionToTrigger.miniActivate()
		var particles = ObjectPool.particleOneShot(activationParticles, get_parent())
		particles.global_position = potionToTrigger.global_position
	
	activate()

func onItemRoll(descr):
	if descr.hasType(Type.Potion) and boostedPotions > 0:
		ItemBook.multiplyWeight(1.5)

func onItemRolled(descr):
	if descr.hasType(Type.Potion):
		boostedPotions -= 1
