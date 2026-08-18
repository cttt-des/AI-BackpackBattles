extends Item

onready var salesChance: = getP("sales") / 100.0
onready var goldCost: = int(getP("gold"))
var active: bool

func _ready():
	if isOwnable():
		Game.connect("switching_to_combat", self, "onSwitchToCombat")

func getData():
	return active

func setData(data):
	active = data

func onSwitchToCombat():
	active = false

func onShopEntered():
	if Game.getGold() >= goldCost:
		Game.spendGold(goldCost)
		activate()
		active = true
		
		Game.saveRunState()
	else:
		active = false
		Game.saveRunState()

func onSaleRoll(_item):
	if active:
		Game.shopSceneNode.addBonusSalesChance(salesChance)

func onSaleRoll_storage(_item):
	onSaleRoll(_item)

func getGatedDescriptor(rarity):
	
	if rarity == Rarity.Common:
		
		var odds = Game.shopSceneNode.getRarityOddsForCurRound().duplicate()
		var nonCommonChance = 1.0 - odds[Rarity.Common]
		odds[Rarity.Common] = 0
		for r in range(Rarity.Rare, Rarity.Godly + 1):
			odds[r] /= nonCommonChance
		rarity = ItemBook.getRandomRarity(odds)
	
	var filter = ItemBook.Filter.OnlyCrafted + ItemBook.Filter.AnyRarity
	var pool = ItemPool.new()
	for descriptor in ItemBook.items.values():
		if ItemBook.canBeGenerated(descriptor, filter):
			if descriptor.getRarity() == rarity:
				pool.addItem(descriptor)
	
	pool.resetPrice()
	
	var item = pool.getRandomItem()
	
	return item

func onGateItemRoll():
	if active:
		.onGateItemRoll()

func onGateItemRoll_storage():
	onGateItemRoll()

