extends Potion

const activationParticles = preload("res://Items/Exclusive/Particles/RainbowPotionActivationParticles.tscn")

onready var buffsNeeded: = int(getP("buffst"))
onready var numPotions: = int(getP("potions"))
onready var buffsPerStaff: = int(getP("buffs"))
onready var manaPerBook: = int(getP("mana"))
onready var staminaPerBook: = int(getP("stamina"))

var usedBuffs: int

func canAffect_global(item):
	return item.hasType(Type.Potion) and item != self

func getAffectedCellsAfterRotate_primary(rotatedCells) -> Array:
	if faceDirection == FaceDirection.LEFT:
		return [rotatedCells[1] + Vector2.UP]
	else:
		return [rotatedCells[0] + Vector2.UP]

func isAffectingDistinct(color = Affected.Primary) -> bool:
	return color == Affected.Secondary or color == Affected.Tertiary

func canAffect_secondary(item):
	return item.hasType(Type.Book)

func canAffect_tertiary(item):
	return item.hasTag(Tag.Staff)

func onTriggerPotion(event = null):
	
	var allPotions = []
	for item in inventory.getItems():
		if canAffect_global(item):
			allPotions.push_back(item)
	allPotions.shuffle()
	




	
	
	var potionsToTrigger = []
	for potion in allPotions:
		var typeExists: = false
		for triggeredPotion in potionsToTrigger:
			if potion.isA(triggeredPotion.descriptor):
				typeExists = true
				break
		if typeExists:
			continue
		potionsToTrigger.push_back(potion)
		if potionsToTrigger.size() == numPotions:
			break
	
	for potion in potionsToTrigger:
		
		potion.triggerPotion(event)
		
		var particles = ObjectPool.particleOneShot(activationParticles, get_parent())
		particles.global_position = potion.global_position

func onPrepare():
	connectToCharacterBuffs("onBuffsChanged")
	usedBuffs = 0

func onCombatStart():
	var books = getNumDistinctAffectedItems(Affected.Secondary)
	if books > 0:
		giveMana(books * manaPerBook)
		giveMaxStaminaTemporary(books * staminaPerBook)
	
	var staffs = getNumDistinctAffectedItems(Affected.Tertiary)
	if staffs > 0:
		giveRandomBuffs(buffsPerStaff * staffs)
	
	
	activate(null, false, false, null, false)

func onBuffsChanged(amount, event):
	if isEmpty(): return
	
	if amount < 0 and event.getParam("used", false):
		
		usedBuffs += int(abs(amount))
		if usedBuffs > buffsNeeded:
			consumePotion(event)

func getGatedDescriptor(_rarity) -> ItemDescriptor:
	return Util.pickRandomElement(ItemBook.staffDescriptors)

func getStarPosition() -> Vector2:
	var cellSize = 2 * halfCellSize.x * global_scale.x
	if faceDirection == FaceDirection.UP:
		return global_position + Vector2( - 0.5 * cellSize, - 1.0 * cellSize)
	elif faceDirection == FaceDirection.DOWN:
		return global_position + Vector2(0.5 * cellSize, - 1.0 * cellSize)
	else:
		return global_position + Vector2(0, - 1.5 * cellSize)
		

func getRelatedItems():
	return ItemBook.staffDescriptors

func getRelatedItemColumns() -> int:
	return 3

func getRelatedItemHeight() -> int:
	return 250
