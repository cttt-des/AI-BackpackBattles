extends "res://Items/Bag.gd"

var affectedPotions: Array
var numConsumed: int

func onPrepare():
	numConsumed = 0
	affectedPotions.clear()
	var affectedItems = getItemsInside()
	for item in affectedItems:
		if canApplyEffect(item):
			affectedPotions.push_back(item)
			connectForCombat(item, "potion_emptied", "onPotionEmptied")

func onPotionEmptied(_potion):
	var numBuffs: = 0
	var active = false
	numConsumed += 1
	
	if numConsumed == 1:
		numBuffs = 1
		active = true
		
	elif numConsumed == 4:
		cleanseRandomDebuffs(getP1())
		active = true
	
	if isTypeInInventory(ItemBook.bagtacularDescriptor):
		numBuffs += int(ItemBook.bagtacularDescriptor.getP("buffs"))
		active = true
	
	if numBuffs > 0:
		giveRandomBuffs(numBuffs)
	
	if active:
		activate()
	








func canApplyEffect(toItem):
	return toItem.hasType(Type.Potion)
