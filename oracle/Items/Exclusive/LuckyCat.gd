extends Item

const noPawSprite = preload("res://Items/Exclusive/Sprites/LuckyCat_no_paw.png")
const leftPawSprite = preload("res://Items/Exclusive/Sprites/LuckyCat_left_paw.png")
const bothPawSprite = preload("res://Items/Exclusive/Sprites/LuckyCat_both_paws.png")

onready var sales = getP("sales") / 100.0
onready var goldThreshold1 = getP("gold1")
onready var goldThreshold2 = getP("gold2")

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
	var colors = [Util.inactiveColor, Util.inactiveColor]
	var gold: int
	
	if placed:
		gold = getCounterValue()
		if condition1Fulfilled(gold):
			colors[0] = Util.modifiedColor
			if condition2Fulfilled(gold):
				colors[1] = Util.modifiedColor
	
	descr = getModeDescription(descr, colors, true, wrapInColor)
	





	return descr


func updatePaws():
	var gold = getCounterValue()
	if condition1Fulfilled(gold):
		if condition2Fulfilled(gold):
			sprite.texture = bothPawSprite
		else:
			sprite.texture = leftPawSprite
	else:
		sprite.texture = noPawSprite
	
	updateShadowTexture()
	

func onAffectedItemAdded(item, color: int):
	updatePaws()

func onAffectedItemRemoved(item, color: int):
	updatePaws()

func onAddToInventory():
	updatePaws()

func onRemoveFromInventory():
	sprite.texture = noPawSprite
	updateShadowTexture()

func canAffect_global(item):
	return item.getRarity() >= Rarity.Godly and item.hasCooldown()

func onSaleRoll(_item):
	Game.shopSceneNode.addBonusSalesChance(sales)
