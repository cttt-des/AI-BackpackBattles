extends Potion
var usedBuffs: int
var buffsNeeded
var numPotions
var buffsPerStaff
var manaPerBook
var staminaPerBook

func canAffect_global(item):
	return item.hasType(CoreConst.Type.Potion) and item != self


func getAffectedCellsAfterRotate_primary(rotatedCells) -> Array:
	if faceDirection == CoreConst.FaceDirection.LEFT:
		return [rotatedCells[1] + Vector2.UP]
	else:
		return [rotatedCells[0] + Vector2.UP]


func isAffectingDistinct(color = CoreConst.Affected.Primary) -> bool:
	return color == CoreConst.Affected.Secondary or color == CoreConst.Affected.Tertiary


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Book)


func canAffect_tertiary(item):
	return item.hasTag(CoreConst.Tag.Staff)


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
		


func onPrepare():
	connectToCharacterBuffs("onBuffsChanged")
	usedBuffs = 0


func onCombatStart():
	var books = getNumDistinctAffectedItems(CoreConst.Affected.Secondary)
	if books > 0:
		giveMana(books * manaPerBook)
		giveMaxStaminaTemporary(books * staminaPerBook)
	
	var staffs = getNumDistinctAffectedItems(CoreConst.Affected.Tertiary)
	if staffs > 0:
		giveRandomBuffs(buffsPerStaff * staffs)
	
	
	activate(null, false, false, null, false)


func onBuffsChanged(amount, event):
	if isEmpty(): return
	
	if amount < 0 and event.getParam("used", false):
		
		usedBuffs += int(abs(amount))
		if usedBuffs > buffsNeeded:
			consumePotion(event)


func getGatedDescriptor(_rarity) -> CoreItemData:
	return null

func getStarPosition() -> Vector2:
	return Vector2.ZERO

func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 3


func getRelatedItemHeight() -> int:
	return 250

func _readyInit():
	._readyInit()
	buffsNeeded = int(getP("buffst"))
	numPotions = int(getP("potions"))
	buffsPerStaff = int(getP("buffs"))
	manaPerBook = int(getP("mana"))
	staminaPerBook = int(getP("stamina"))
