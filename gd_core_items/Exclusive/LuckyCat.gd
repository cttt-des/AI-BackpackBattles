extends Item
var sales
var goldThreshold1
var goldThreshold2

func canAffect(item):
	return true


func getCounterValue() -> int:
	return getAffectedGoldValue()


func condition1Fulfilled(gold: int) -> bool:
	return gold > goldThreshold1


func condition2Fulfilled(gold) -> bool:
	return gold > goldThreshold2


func onPrepare():
	var gold = getCounterValue()
	if condition1Fulfilled(gold):


		character().changeCritResistance(getChance())
		
		if condition2Fulfilled(gold):
			var bonusSpeed = getP("speed") / 100.0
			for item in inventory.getItems():
				if canAffect_global(item):
					item.addSpeed(bonusSpeed)
		
	


func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var colors = [ctx.util.inactiveColor, ctx.util.inactiveColor]
	var gold: int
	
	if placed:
		gold = getCounterValue()
		if condition1Fulfilled(gold):
			colors[0] = ctx.util.modifiedColor
			if condition2Fulfilled(gold):
				colors[1] = ctx.util.modifiedColor
	
	descr = getModeDescription(descr, colors, true, wrapInColor)
	





	return descr



func updatePaws():
	var gold = getCounterValue()
	if condition1Fulfilled(gold):
		if condition2Fulfilled(gold):
			pass
		else:
			pass
	else:
		pass
	
	updateShadowTexture()
	


func onAffectedItemAdded(item, color: int):
	updatePaws()


func onAffectedItemRemoved(item, color: int):
	updatePaws()


func onAddToInventory():
	updatePaws()


func onRemoveFromInventory():
	updateShadowTexture()


func canAffect_global(item):
	return item.getRarity() >= CoreConst.Rarity.Godly and item.hasCooldown()


func onSaleRoll(_item):
	pass

func _readyInit():
	._readyInit()
	sales = getP("sales") / 100.0
	goldThreshold1 = getP("gold1")
	goldThreshold2 = getP("gold2")
