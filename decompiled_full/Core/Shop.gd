extends Node2D

signal gate_item_roll
signal roll_sale
signal shop_refreshed

const shopOpenSound = preload("res://Assets/Sound/ShopBell.ogg")
const rerollSound = preload("res://Assets/Sound/Bell_short.ogg")
const throwOutSound = preload("res://Assets/Sound/Throwaway.mp3")
const notEnoughGoldLabel = preload("res://Interface/NotEnoughGoldLabel.tscn")
const highRollParticlesScene = preload("res://Interface/HighRollParticles2D.tscn")
const skillRoundSound = preload("res://Assets/Sound/LevelUp1.ogg")

onready var slots = [
	$ShopOffer1, 
	$ShopOffer2, 
	$ShopOffer3, 
	$ShopOffer4, 
	$ShopOffer5
]

onready var shopSignLabel = $ShopLabel
onready var chooseOneLabel = $ChooseOneLabel
onready var itemOffScreenIndicator = $OffScreenItemIndicator

onready var redArrowAnimation = $Reroll / RedArrowAnimationPlayer
onready var redArrow = $Reroll / RedArrow
onready var rarityChart = $ShopSign / RarityChart

var rarityOdds = [
	[0.9, 0.1, 0.0, 0.0, 0.0], 
	[0.84, 0.15, 0.01, 0.0, 0.0], 
	[0.75, 0.2, 0.05, 0.0, 0.0], 
	[0.64, 0.25, 0.1, 0.01, 0.0], 
	[0.45, 0.35, 0.15, 0.05, 0.0], 
	[0.29, 0.4, 0.2, 0.1, 0.01], 
	[0.2, 0.35, 0.25, 0.15, 0.05], 
	[0.2, 0.3, 0.25, 0.15, 0.1], 
	[0.2, 0.28, 0.25, 0.15, 0.12], 
	[0.2, 0.25, 0.25, 0.15, 0.15], 
	[0.2, 0.23, 0.23, 0.17, 0.17], 
	[0.2, 0.2, 0.2, 0.2, 0.2]
]















var gateItemCandidates: Array

onready var megaCloverDescriptor = ItemBook.getDescriptor("Mega Clover")
onready var kingoftheBlingDescriptor = ItemBook.getDescriptor("King of the Bling")

var itemsBoughtThisRound: int
var rerollsThisRound: int
var rerollsThisRun: int
var rollsThisRun: int
var saleAcc = 0.0

var saleSlots: = []
var stashedItems: = []
var stashedSales: = []
var stashedItemData: = []
var encounteredRoll: Array
var rerolledRoll: Array
const REROLL_THRESHOLD1 = 4
const REROLL_THRESHOLD2 = 9999999
const SALE_CHANCE = 0.1
const UNIQUE_CHANCES = [
	0.3, 0.2, 0.2, 0.07
	
	]
var rolledUnique = null
var uniqueAcc = 0.0
var chooseOneShop: bool = false
var bonusSaleChance: float
var reservedItemsCounter: Dictionary

func _ready() -> void :
	Game.connect("shop_opened", self, "openShop")
	Game.connect("switch_to_shop", self, "enteringShop")
	Game.connect("shop_closed", self, "closeShop")
	Game.connect("returned_to_title", self, "clear")
	Game.connect("run_over", self, "resetRerollCounter")
	Game.connect("item_picked_up", self, "onItemPickedUp")
	Game.connect("item_dropped", self, "onItemDropped")
	bannerTimer.connect("timeout", self, "onBannerTimerTimeout")
	resetRerollCounter()
	
	if Util.isChristmas():
		var snowglobe = load("res://Assets/Decoration/SnowGlobe.tscn").instance()
		add_child(snowglobe)
	





func resetRerollCounter():
	rerollsThisRun = 0
	rollsThisRun = 0
	saleAcc = 0.0
	uniqueAcc = 0.0
	
	encounteredRoll.clear()
	rerolledRoll.clear()
	for item in ItemBook.getNumItems():
		encounteredRoll.push_back(ItemBook.NOT_ENCOUNTERED)
		rerolledRoll.push_back(ItemBook.NOT_ENCOUNTERED)

func getRerollCost() -> int:
	if rerollsThisRound < REROLL_THRESHOLD1:
		return 1
	elif rerollsThisRound < REROLL_THRESHOLD2:
		return 2
	else:
		return 3

func getRerollProgress() -> float:
	if rerollsThisRound <= REROLL_THRESHOLD1:
		return rerollsThisRound / float(REROLL_THRESHOLD1)
	elif rerollsThisRound <= REROLL_THRESHOLD2:
		return (rerollsThisRound - REROLL_THRESHOLD1) / float(REROLL_THRESHOLD2 - REROLL_THRESHOLD1)
	else:
		return 1.0

func enteringShop():
	if Game.runWasJustContinued:
		rerollsThisRound = Game.getRunState()["rerolls"]
	else:
		rerollsThisRound = 0
	
	ItemBook.countItems()
	


func openShop():
	rolledUnique = null
	itemsBoughtThisRound = 0
	chooseOneShop = false
	chooseOneLabel.hide()
	shopSignLabel.show()
	
	saleSlots.clear()
	if isFirstShop():
		
		var indices = range(0, 5)
		indices.shuffle()
		saleSlots.push_back(indices[0])
		saleSlots.push_back(indices[1])
	




	
	Sound.playSound(shopOpenSound)
	
	var makeNewShop = true
	
	if Game.runWasJustContinued:
		if Game.continueState == Game.ContinueState.FromShop:
			if not stashedItems.empty():
				chooseOneShop = true
				showChooseOneSign()
					
			makeNewShop = false
			
		
			
	
	if makeNewShop:
		if (Game.curRound == Game.SUBCLASS_ROUND and 
			( not Game.ENGINEER_TEST or Game.curClass != Game.Classes_Full.Engineer)):
			showSubclassShop()
		elif (Game.SKILLS_ENABLED and 
			(Game.curRound == Game.SKILL_ROUND1 or 
				Game.curRound == Game.SKILL_ROUND2)):
			showSkillShop()
		else:
			showNormalShop()
	
	if SteamHelper.is_init():
		SteamHelper.dropItem()

func closeShop():
	Util.callDelayed(self, "shopHidden", 2)
	
	
	
	
	
	if Game.ACHIEVEMENTS_ENABLED and not SteamHelper.hasAchievement("Reserve"):
		var reserved = {}
		for slot in slots:
			if slot.reserved:
				var descr = slot.item.descriptor
				
				var numRoundsReserved = reservedItemsCounter.get(descr, 0) + 1
				if numRoundsReserved >= 3:
					SteamHelper.unlockAchievement("Reserve")
					break
				else:
					reserved[slot.item.descriptor] = numRoundsReserved
		
		reservedItemsCounter = reserved
	
	
	
	
	
func shopHidden():
	chooseOneShop = false
	
	resetAll()

func stashItems():
	for i in slots.size():
		if slots[i].reserved:
			stashedItems.push_back(ItemBook.getItemIndex(slots[i].item))
			stashedSales.push_back(slots[i].onSale)
			
			var persistentData = slots[i].item.getData()
			stashedItemData.push_back(persistentData)
			
		else:
			stashedItems.push_back( - 1)
			stashedSales.push_back( - 1)
			stashedItemData.push_back(null)
	
		slots[i].resetFull()

func resetAll():
	for slot in slots:
		slot.reset()

func throwAllOut():
	for slot in slots:
		slot.throwOut()

func unstashItems():
	for i in stashedItems.size():
		if stashedItems[i] != - 1:
			var saleMode = Game.SaleMode.Sale if stashedSales[i] else Game.SaleMode.NoSale
			slots[i].setItem(ItemBook.instantiateItemFromIndex(stashedItems[i]), saleMode)
			slots[i].setReserved(true)
			if stashedItemData[i] != null:
				slots[i].item.setData(stashedItemData[i])
	
	stashedItems.clear()
	stashedSales.clear()
	stashedItemData.clear()

func showChooseOneSign():
	if not Game.SKILLS_ENABLED: return
	
	shopSignLabel.hide()
	chooseOneLabel.show()
	if Game.curRound == Game.SUBCLASS_ROUND:
		chooseOneLabel.translationKey = "UI_ChooseSubclass"
	else:
		chooseOneLabel.translationKey = "UI_ChooseSkill"
	chooseOneLabel.updateLocale()
	
	rarityChart.disappear()
	bannerTimer.start(bannerHighlightInterval)

func showSubclassShop():
	if not chooseOneShop:
		chooseOneShop = true
		
		showChooseOneSign()
		
		stashItems()
		
		var subclassItems = ItemBook.getSubclassItemDescr(Game.curClass)

		slots[0].setItem(ItemBook.instantiateItem(subclassItems[0]), Game.SaleMode.Roll)
		slots[4].setItem(ItemBook.instantiateItem(subclassItems[1]), Game.SaleMode.Roll)
		slots[2].setItem(ItemBook.instantiateItem(subclassItems[2]), Game.SaleMode.Roll)
		
		if subclassItems.size() == 5:
			slots[3].setItem(ItemBook.instantiateItem(subclassItems[3]), Game.SaleMode.Roll)
			slots[1].setItem(ItemBook.instantiateItem(subclassItems[4]), Game.SaleMode.Roll)
		
		for slot in slots:
			if slot.item != null:
				Game.incrementItemStatistic(Game.ItemStatistic.SeenInShop, slot.item.descriptor)
		
		Sound.playSound(skillRoundSound, - 4, 1.1)
		
		Game.saveRunState()
		emit_signal("shop_refreshed")

func onChooseOneItemBought(item):
	Game.onSpecialItemBought(item)
	endChooseOneShop()
	rollItems(getHighRollBuckets(), getUniqueSlots(), item)


func showNormalShop():
	if Game.getTotalRotations() == 0 and Game.curRound == 2:
		var rotateHint = load("res://Interface/RotateHint.tscn").instance()
		Game.UINode.add_child(rotateHint)
	
	if Game.getTotalRerolls() == 0 and Game.curRound == 4:
		redArrowAnimation.play("ShowArrow")
	
	resetAll()
	unstashItems()
	rollItems(getHighRollBuckets(), getUniqueSlots())

func showSkillShop():
	if not chooseOneShop:
		chooseOneShop = true
		
		showChooseOneSign()
		stashItems()
		
		
		var skills = ItemBook.getRandomSkills()
		
		slots[0].setItem(ItemBook.instantiateItem(skills[0]), Game.SaleMode.Roll)
		slots[4].setItem(ItemBook.instantiateItem(skills[1]), Game.SaleMode.Roll)
		slots[2].setItem(ItemBook.instantiateItem(skills[2]), Game.SaleMode.Roll)
		if Game.curRound == Game.SKILL_ROUND1:
			slots[1].setItem(ItemBook.instantiateItem(ItemBook.justStatsDescriptor), Game.SaleMode.Roll)
		else:
			slots[1].setItem(ItemBook.instantiateItem(ItemBook.moreStatsDescriptor), Game.SaleMode.Roll)
		
		var unidentifiedSkill = ItemBook.instantiateItem(ItemBook.unidentifiedSkillDescriptor)
		slots[3].setItem(unidentifiedSkill, Game.SaleMode.Roll)
		
		for slot in slots:
			if slot.item != null:
				Game.incrementItemStatistic(Game.ItemStatistic.SeenInShop, slot.item.descriptor)
		
		Sound.playSound(skillRoundSound)
		
		Game.saveRunState()
		emit_signal("shop_refreshed")
	
	

func endChooseOneShop():
	chooseOneShop = false
	chooseOneLabel.hide()
	shopSignLabel.show()
	throwAllOut()
	unstashItems()
	rarityChart.appear()
	bannerTimer.stop()

func getUniqueSlots() -> Array:
	var uniqueSlots = []
	var uniquesAllowed = ItemBook.getMaxUniques() - ItemBook.getNumUniques()
	
	if uniquesAllowed > 0:
		var uniqueChance = getUniqueChance()
		uniqueAcc += uniqueChance
		var nonReserved = getNonReservedSlotIndices()
		
		var uniques: int = Util.flipRound(uniqueChance)
		if uniques == 0 and uniqueAcc > 1.2:
			uniques = 1
		
		uniques = min(uniques, min(nonReserved.size(), uniquesAllowed))
		
		
		for i in uniques:
			var slot = nonReserved[0]
			nonReserved.erase(slot)
			uniqueAcc = 0.0
			uniqueChance -= 1.0
			uniqueSlots.push_back(slot)
			uniquesAllowed -= 1
			
	return uniqueSlots

func getSaleChance(item = null):
	var chance = SALE_CHANCE
	
	bonusSaleChance = 0
	emit_signal("roll_sale", item)
	
	chance += bonusSaleChance
	
	if CustomRules.customRulesActive:
		chance += CustomRules.getRuleValue(CustomRules.Rules.SalesChance) / 100.0
	
	return chance

func getUniqueChance():
	var uniqueChance = UNIQUE_CHANCES[min(Game.curRound - 1, UNIQUE_CHANCES.size() - 1)]
	
	if ItemBook.isItemInInventory(megaCloverDescriptor):
		uniqueChance += megaCloverDescriptor.getP("uniques") / 100.0
	
	var platCards = ItemBook.countItemsInInventoryOfType(ItemBook.platinCardDescriptor)
	uniqueChance += platCards * ItemBook.platinCardDescriptor.getP("uniques") / 100.0
	
	var stars = ItemBook.countItemsInInventoryOfType(ItemBook.starOfCourageDescriptor)
	uniqueChance += stars * ItemBook.starOfCourageDescriptor.getP("uniques") / 100.0
	
	if ItemBook.isItemInInventory(ItemBook.uniquelyUniqueDescriptor):
		uniqueChance += ItemBook.uniquelyUniqueDescriptor.getP("uniques") / 100.0
	
	if ItemBook.isItemInInventory(ItemBook.fedoraDescriptor):
		uniqueChance += ItemBook.fedoraDescriptor.getP("uniques") / 100.0
	
	uniqueChance += CustomRules.getBonusUniqueChance() / 100.0
	
	return uniqueChance

func getNonReservedSlotIndices():
	var nonReservedSlots = []
	for i in slots.size():
		if not slots[i].reserved:
			nonReservedSlots.push_back(i)
	
	return nonReservedSlots
	
func getHighRollBuckets():
	var highRollBuckets = [0, 0, 0, 0, 0]
	
	var nonReservedSlots = getNonReservedSlotIndices()
	if not nonReservedSlots.empty():
		
		for item in ItemBook.getItemsInInventoryOfType(ItemBook.customerCardDescriptor):
			var slotIndex = Util.pickRandomElement(nonReservedSlots)
			highRollBuckets[slotIndex] += 1
			spawnHighRollParticles(slotIndex)
			item.activate()
	return highRollBuckets









func addGateItem(item):
	gateItemCandidates.push_back(item)

func getFreeSlot(excludedSlots) -> int:
	var nonReservedSlots = getNonReservedSlotIndices()
	nonReservedSlots = Util.subtractArr(nonReservedSlots, excludedSlots)
	if not nonReservedSlots.empty():
		return nonReservedSlots[0]
	else:
		return - 1

func getRarityOddsForCurRound():
	var index = min(rarityOdds.size() - 1, Game.curRound - 1)
	return rarityOdds[index]

func isFirstShop() -> bool:
	return Game.curRound == 1 and rerollsThisRound == 0

func hasWeapon(items) -> bool:
	for item in items:
		if item.descriptor.isStartingWeapon():
			return true
	return false

func rollItems(highRollBuckets = [0, 0, 0, 0, 0], uniqueSlots = [], triggeringSubclassItem = null):
	ItemBook.countItems()
	var inventoryDict = ItemBook.getInventoryAsDict()
	
	gateItemCandidates.clear()
	emit_signal("gate_item_roll")
	gateItemCandidates.shuffle()
	
	
	rollsThisRun += 1
	
	var gatedSlots = {}
	
	var excluded = uniqueSlots.duplicate()
	
	if triggeringSubclassItem != null and triggeringSubclassItem.has_method("getGatedDescriptor"):
		var slot = getFreeSlot(excluded)
		gatedSlots[slot] = triggeringSubclassItem
		excluded.push_back(slot)
	








	
	
	
	for gateItem in gateItemCandidates:
		var slot = getFreeSlot(excluded)
		if slot == - 1:
			Util.eassert(false)
			break
		gatedSlots[slot] = gateItem
		excluded.push_back(slot)
	
	
	
	var forgingHammerSlot = - 1
	var forgingHammerOdds: float = 0.07
	if (encounteredRoll[ItemBook.forgingHammerDescriptor.itemIndex] == ItemBook.NOT_ENCOUNTERED and 
		Game.SELLBOX.getLastSellRoll(ItemBook.forgingHammerDescriptor) == ItemBook.NOT_SOLD):
		forgingHammerOdds = 0.2
	if Game.curClass != Game.Classes_Full.Berserker:
		forgingHammerOdds *= 0.7
	
	
	if Util.flip(forgingHammerOdds) and ItemBook.canGetForgingHammer(inventoryDict):
		forgingHammerSlot = getFreeSlot(excluded)
	
	var rolledItems = []
	
	
	
	for i in slots.size():
		if not slots[i].reserved:
			
			var item
			if i in uniqueSlots:
				item = ItemBook.getRandomUnique()
				rolledUnique = item
				Game.incrementItemStatistic(Game.ItemStatistic.SeenInShop, 
					item.descriptor)
			else:
				var rarity = ItemBook.getRandomRarity(getRarityOddsForCurRound())
				rarity = min(Item.Rarity.Godly, rarity + highRollBuckets[i])
				
				if isFirstShop():
					if i == 4 and not hasWeapon(rolledItems):
						item = ItemBook.randomWeaponOfRarity(rarity, 
							ItemBook.descriptorsFromItemList(rolledItems), 
							encounteredRoll, rollsThisRun)
					else:
						item = ItemBook.randomNonBagOfRarity(rarity, 
							ItemBook.descriptorsFromItemList(rolledItems), 
							encounteredRoll, rollsThisRun)
				
				elif i in gatedSlots:
					var descriptor
					if (gatedSlots[i].isA(ItemBook.boxOfRichesDescriptor) or 
						gatedSlots[i].isA(ItemBook.piggyOfRichesDescriptor)):
						descriptor = gatedSlots[i].getGatedDescriptor(getRarityOddsForCurRound(), highRollBuckets[i])
					else:
						descriptor = gatedSlots[i].getGatedDescriptor(rarity)
					item = ItemBook.instantiateItem(descriptor)
					
				elif i == forgingHammerSlot:
					item = ItemBook.instantiateItem(ItemBook.forgingHammerDescriptor)
				
				elif Game.bagPityCounter == Game.BAG_PITY_TIMER:
					item = ItemBook.randomBagOfRarity(rarity, 
						ItemBook.descriptorsFromItemList(rolledItems))
					resetBagPity()
					
				else:
					item = ItemBook.randomItemOfRarity(rarity, 
						ItemBook.descriptorsFromItemList(rolledItems), 
						encounteredRoll, rollsThisRun)
				
					if item.isBag():
						resetBagPity()
					else:
						Game.bagPityCounter += 1
				
				rolledItems.push_back(item)
				encounteredRoll[ItemBook.getItemIndex(item)] = rollsThisRun
			
			slots[i].setItem(item)
			item.popIn(true, Util.rng.randf_range(0.8, 1.2), true)
	
	for item in rolledItems:
		Game.incrementItemStatistic(Game.ItemStatistic.SeenInShop, 
			item.descriptor)
	
	emit_signal("shop_refreshed")
	Game.saveRunState()
	Game.writeoutState()
	checkSalesAch()
	
	
	
	
func resetBagPity():
	Game.bagPityCounter = [0, 1, 2].pick_random()

func checkSalesAch():
	var numOnSale = 0
	for slot in slots:
		if slot.onSale:
			numOnSale += 1
	if numOnSale == 5:
		SteamHelper.unlockAchievement("Sale")

func clear():
	for slot in slots:
		slot.resetFull()
	stashedItems.clear()
	stashedSales.clear()
	stashedItemData.clear()
	chooseOneShop = false
	chooseOneLabel.hide()
	shopSignLabel.show()
	reservedItemsCounter.clear()

func setItem(slotIndex, item):
	
	
	var saleMode = Game.SaleMode.Roll
	if chooseOneShop:
		saleMode = Game.SaleMode.NoSale
	slots[slotIndex].setItem(item)
	item.popIn()


func setBought(slotIndex):
	slots[slotIndex].resetFull()


func setReserved(slotIndex, reserved):
	slots[slotIndex].setReserved(reserved)


func setOnSale(slotIndex, onSale):
	if onSale:
		slots[slotIndex].setSaleMode(Game.SaleMode.Sale)
	else:
		slots[slotIndex].setSaleMode(Game.SaleMode.NoSale)
	slots[slotIndex].calcPrice()


func setStashedReservedItems(_stashedItems):
	if _stashedItems != null:
		
		stashedItems = _stashedItems.duplicate()

func setStashedSales(_stashedSales):
	if _stashedSales != null:
		stashedSales = _stashedSales.duplicate()

func setStashedItemData(_stashedItemData):
	if _stashedItemData != null:
		stashedItemData = _stashedItemData.duplicate()

func getItems():
	var items = []
	for i in slots.size():
		if slots[i].bought:
			items.push_back(null)
		else:
			items.push_back(slots[i].item)
	return items

func getItemsNoNull():
	return Util.filterNull(getItems())

func getReservedSlots():
	var reserved = []
	for i in slots.size():
		reserved.push_back(slots[i].reserved)
	return reserved

func getReservedItemsNoNull():
	var items = []
	for i in slots.size():
		if slots[i].reserved:
			items.push_back(slots[i].item)
	return items

func getSaleSlots():
	var onSale = []
	for i in slots.size():
		onSale.push_back(slots[i].onSale)
	return onSale


func getStashedReservedItems():
	if chooseOneShop:
		return stashedItems.duplicate()
	else:
		return null

func getStashedSales():
	if chooseOneShop:
		return stashedSales.duplicate()
	else:
		return null

func getStashedItemData():
	if chooseOneShop:
		return stashedItemData.duplicate()
	else:
		return null

func reroll():
	saleSlots.clear()
	
	if chooseOneShop:
		endChooseOneShop()
		SteamHelper.unlockAchievement("NoSkill")
	
	var cost = getRerollCost()
	rerollsThisRound += 1
	rerollsThisRun += 1
	Game.persistent["rerolls"] += 1
	
	if Game.getTotalRerolls() == 1 and redArrow.visible:
		redArrowAnimation.play("HideArrow")
		Game.saveGame()
	
	Game.spendGold(cost)
	var coinParticles = Game.shootGold(Game.PLAYER.getGoldPos(), Game.SELLBOX.getGoldPos(), cost)
	coinParticles.z_index = Game.getCoinPlayerLayer()
	Util.setDelayed(coinParticles, "z_index", Game.getCoinSellboxLayer(), 0.5)
	Util.callDelayed(Game.SELLBOX, "eatGold", 0.3, [cost])
	
	for slot in slots:
		if slot.canThrowOut():





			
			
			rerolledRoll[ItemBook.getItemIndex(slot.item)] = rollsThisRun
			slot.throwOut()
	
	
	
	rollItems(getHighRollBuckets())
	
	Sound.playSound(rerollSound, 6, Util.rng.randf_range(0.95, 1.05))
	Sound.playSound(throwOutSound, 12, Util.rng.randf_range(0.95, 1.05))
	

func spawnHighRollParticles(slotIndex):
	var particles = ObjectPool.instance(highRollParticlesScene)
	add_child(particles)
	particles.global_position = slots[slotIndex].global_position
	particles.restart()
	ObjectPool.returnAfter(1, particles)
	return particles


func rollSale(slot) -> bool:
	
	if not saleSlots.empty():
		if slot.index in saleSlots:
			saleSlots.erase(slot.index)
			return true
	
	var isSale = false
	
	var saleChance = getSaleChance(slot.item)
	if CustomRules.isRuleDefault(CustomRules.Rules.SalesChance):
		saleChance *= slot.item.getSalesMultiplier()
	
	if Util.flip(saleChance):
		isSale = true
	else:
		saleAcc += saleChance
		if saleAcc > 1.3:
			isSale = true
	
	if isSale:
		saleAcc = 0.0
	
	return isSale

func addBonusSalesChance(chance):
	bonusSaleChance += chance

var bannerTween: SceneTreeTween
onready var bannerTimer = $BannerTimer


func onItemPickedUp():
	if (Game.draggedItem.ownerType == Item.Owner.Shop and 
		(Game.draggedItem.isSubclassItem() or Game.draggedItem.hasType(Item.Type.Skill))):
		
		bannerTimer.stop()
		bannerTween = Util.refreshTween(bannerTween).set_parallel()
		
		for slot in slots:
			if slot.item == Game.draggedItem:
				bannerTween.tween_property(slot.subclassLabel, "modulate", Color(1.2, 1.2, 1.2), 0.15)
			else:
				bannerTween.tween_property(slot.subclassLabel, "modulate", Color(0.8, 0.8, 0.8), 0.15)

func onItemDropped(item, dropResult: int):
	if dropResult == Item.DropResult.OutsideInventory:
		if (Game.draggedItem.ownerType == Item.Owner.Shop and 
			(Game.draggedItem.isSubclassItem() or Game.draggedItem.hasType(Item.Type.Skill))):
			
			bannerTween = Util.refreshTween(bannerTween).set_parallel()
			
			for slot in slots:
				bannerTween.tween_property(slot.subclassLabel, "modulate", Color(1, 1, 1), 0.1)
			
			bannerTimer.start(bannerHighlightInterval)

var nextHighlightSlot: int
const bannerHightlightColor = Color(1.4, 1.4, 1.4)
const bannerHighlightDur = 2.3
const bannerHighlightDur2 = 2.69
const bannerHighlightInterval = 5.0
const highlightSlots = [1, 0, 4, 2, 3]

func onBannerTimerTimeout():
	bannerTween = Util.refreshTween(bannerTween).set_parallel()
	var slot = slots[highlightSlots[nextHighlightSlot]]
	bannerTween.tween_property(slot.subclassLabel, "modulate", bannerHightlightColor, bannerHighlightDur)
	bannerTween.tween_property(slot.subclassLabel, "modulate", Color.white, bannerHighlightDur2).from(bannerHightlightColor).set_delay(bannerHighlightDur)
	nextHighlightSlot = (nextHighlightSlot + 1) % slots.size()
	
func onItemBought(item, slot):
	itemsBoughtThisRound += 1
	
	if item.isTreasure():
		SteamHelper.unlockAchievement("TreasureBought")
	
	var itemsLeft = 0
	for slot in slots:
		if not slot.bought:
			itemsLeft += 1
	if itemsLeft == 0:
		SteamHelper.unlockAchievement("AllBought")
	
	var numBought = SteamHelper.changeStat("ItemsBought", 1)
	if numBought >= 10000:
		SteamHelper.unlockAchievement("ItemsBought2")
	elif numBought >= 1000:
		SteamHelper.unlockAchievement("ItemsBought1")
	
	var replaceItem = null
	
	if chooseOneShop:
		onChooseOneItemBought(item)

	elif item.isA(ItemBook.deckOfCardsDescriptor):
		var cardRarity = ItemBook.getRandomRarity(getRarityOddsForCurRound())
		
		replaceItem = ItemBook.instantiateItem(item.getGatedDescriptor(cardRarity))
	
	elif item.hasType(Item.Type.Food):
		var amulets = ItemBook.getItemsInInventoryOfType(ItemBook.amuletOfFeastingDescriptor)
		if not amulets.empty():
			var rarity = ItemBook.getRandomRarity(getRarityOddsForCurRound())
			replaceItem = ItemBook.instantiateItem(amulets[0].getReplaceDescriptor(rarity))
	
	elif item.hasType(Item.Type.Bag):
		var puzzleboxOrBadge = Util.getArrayElement(ItemBook.getItemsInInventoryOfType(
				ItemBook.puzzleboxDescriptor), 0, null)
		
		if puzzleboxOrBadge == null:
			puzzleboxOrBadge = Util.getArrayElement(ItemBook.getItemsInInventoryOfType(
				ItemBook.puzzleBadgeDescriptor), 0, null)
		
		if puzzleboxOrBadge != null and puzzleboxOrBadge.rollShopChance():
			var rarity = ItemBook.getRandomRarity(getRarityOddsForCurRound())
			replaceItem = ItemBook.instantiateItem(puzzleboxOrBadge.getReplaceDescriptor(rarity))
	
	elif item.isA(ItemBook.twineDescriptor):
		var sewingCaseOrBadge = Util.getArrayElement(ItemBook.getItemsInInventoryOfType(
			ItemBook.sewingCaseDescriptor), 0, null)
		
		if sewingCaseOrBadge == null:
			sewingCaseOrBadge = Util.getArrayElement(ItemBook.getItemsInInventoryOfType(
				ItemBook.classBadges[Game.Classes_Full.Adventurer]), 0, null)
		
		if sewingCaseOrBadge != null and sewingCaseOrBadge.rollShopChance():
			replaceItem = ItemBook.instantiateItem(ItemBook.twineDescriptor)
	
	elif item.hasType(Item.Type.Spell) and item.descriptor in ItemBook.scrolls:
		var arcaneIntellect = Util.getArrayElement(ItemBook.getItemsInInventoryOfType(
			ItemBook.arcaneIntellectDescriptor), 0, null)
		
		if arcaneIntellect != null and arcaneIntellect.rollShopChance():
			replaceItem = ItemBook.instantiateItem(arcaneIntellect.getRandomScroll())
	
	elif item.hasType(Item.Type.Book):
		var arcaneIntellect = Util.getArrayElement(ItemBook.getItemsInInventoryOfType(
			ItemBook.arcaneIntellectDescriptor), 0, null)
		
		if arcaneIntellect != null and arcaneIntellect.rollShopChance(arcaneIntellect.getP("bookchance")):
			replaceItem = ItemBook.instantiateItem(arcaneIntellect.getRandomBook())
	
	elif item.isA(ItemBook.coilDescriptor):
		replaceItem = ItemBook.instantiateItem(ItemBook.batteryDescriptor)
	
	elif item.hasType(Item.Type.Accessory):
		var kingoftheBling = Util.getArrayElement(ItemBook.getItemsInInventoryOfType(
			kingoftheBlingDescriptor), 0, null)
		
		if kingoftheBling != null and kingoftheBling.rollShopChance():
			replaceItem = ItemBook.instantiateItem(kingoftheBling.getRestockItem())
	
	if replaceItem != null:
		slot.setItem(replaceItem)
		replaceItem.popIn()
		Game.incrementItemStatistic(Game.ItemStatistic.SeenInShop, 
			replaceItem.descriptor)
		Game.saveRunState()
		checkSalesAch()

static func notEnoughGold(pos):
	var label = ObjectPool.instance(notEnoughGoldLabel)
	Game.UINode.add_child(label)
	label.global_position = pos
