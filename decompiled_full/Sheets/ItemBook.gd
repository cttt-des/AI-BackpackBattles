extends Node

signal item_instantiated_deferred
signal pre_item_roll
signal item_rolled
signal items_counted

const NUM_PARAMS = 10
const NOT_ENCOUNTERED = - 1000
const NOT_SOLD = - 1001
const COMPLETION_THRESHOLD = 0.5
const COMPLETION_WEIGHT = 0.8
const DUAL_CLASS_WEIGHT = 2.0

var preparedItemInstances: Dictionary
var prepareQueue: Array
var prepareDisableFrame: int

var rarityWeightedBag = WeightedBag.new()
var randomItemWeightedBag = WeightedBag.new()

var table
var items: Dictionary
var shopBags: Array
var bagsForRarity: Array
var curShopClasses: int = ItemDescriptor.StuffedClasses.None
var curShopItems: Array
var descriptorList: Array
var sheetList: Array

var classSpecificItems: Array
var uniqueItems: Array
var subclassUniques: Array

var numSockets: Array

var gemIndex: Dictionary
var gemList: Array
var gemsForRarity: Array
var itemCounter: Dictionary
var ownableItems: Dictionary
var opponentItems: Dictionary

var boxOfRichesDescriptor
var deckOfCardsDescriptor
var crossbladesDescriptor
var missingCrossbladeIngredients
var recipeIngredientsWeights: Dictionary
var customerCardDescriptor
var platinCardDescriptor
var staminaSackDescriptor
var presentDescriptor
var flameDescriptor
var rainbowBadgeDescriptor
var stoneBadgeDescriptor
var forgingHammerDescriptor
var amuletDescriptor
var amuletOfFeastingDescriptor
var amulets: Array
var starOfCourageDescriptor
var toolboxDescriptor
var stableRecombobulatorDescriptor
var unstableRecombobulatorDescriptor
var extraBagsDescriptor
var spiritCompanionDescriptors: Array
var spiritBellsDescriptor
var bagOfGivingDescriptor
var chessboardDescriptor
var staffDescriptors: Array
var puzzleBags: Array
var snowmanDescriptor
var uniquelyUniqueDescriptor
var bagtacularDescriptor
var digDeeperDescriptor
var skills: = [[], []]

var classBadges: Dictionary
var foodsForRarity: Array
var typesWithIcons: Array
var justStatsDescriptor
var moreStatsDescriptor
var unidentifiedSkillDescriptor
var nonGeneratableSkills: Dictionary
var puzzleboxDescriptor
var puzzleBadgeDescriptor
var sewingCaseDescriptor
var twineDescriptor
var arcaneIntellectDescriptor
var scrolls: Array
var books: Array
var fedoraDescriptor
var piggyOfRichesDescriptor
var piggies: Dictionary

var batteryDescriptor
var coilDescriptor
var chargeSplitterDescriptor
var manaCrystalDescriptor
var lightningStaffDescriptor
var boxofCogsDescriptor
var cogDescriptor
var generatorDescriptor
var cogBadgeDescriptor
var contraptronDescriptor
var bloodAmuletDescriptor
var magicRingDescriptor
var superiorRingDescriptor
var hyperCubeDescriptor
var hyperCubes: = []

const amuletNames = [
	"Amulet of Life", 
	"Amulet of Steel", 
	"Amulet of Feasting", 
	"Amulet of Darkness", 
	"Amulet of Agility", 
	"Amulet of the Wild", 
	"Amulet of Alchemy", 
	"Amulet of Fortune", 
	"Amulet of Light"
	]

const typeToTextEffect = {
	Item.Type.Ice: ItemToolTip.TextEffect.Ice, 
	Item.Type.Fire: ItemToolTip.TextEffect.Fire, 
	Item.Type.Holy: ItemToolTip.TextEffect.Light, 
	Item.Type.Vampiric: ItemToolTip.TextEffect.Vampiric, 
	Item.Type.Dark: ItemToolTip.TextEffect.Spooky, 
	Item.Type.Nature: ItemToolTip.TextEffect.Nature, 
	Item.Type.Magic: ItemToolTip.TextEffect.Magic
}

func descriptorsFromItemList(_itemList) -> Array:
	var descriptors = []
	for item in _itemList:
		descriptors.push_back(item.descriptor)
	return descriptors

func descriptorsFromNameList(_nameList) -> Array:
	var descriptors = []
	for itemName in _nameList:
		descriptors.push_back(getDescriptor(itemName))
	return descriptors

func getDescriptor(itemName):
	return items[itemName]

func getNumItems() -> int:
	return items.size()

func getNumGems() -> int:
	return gemList.size()

func prepareInstance(descriptor, num = 1):
	for i in num:
		prepareQueue.push_back(descriptor)
	
func pausePrepare(numFrames: int = 1):
	prepareDisableFrame = Engine.get_physics_frames() + numFrames

func prepareItemInstances():
	
	if Engine.get_physics_frames() <= prepareDisableFrame: return
	if prepareQueue.empty(): return
	
	var descriptor = prepareQueue.pop_back()
	var item = descriptor.instantiate()
	Util.dictAppend(preparedItemInstances, descriptor, item)
	
	


func instantiateItem(descriptorOrName):
	var item
	var descriptor
	if descriptorOrName is String:
		descriptor = items[descriptorOrName]
	else:
		descriptor = descriptorOrName
	
	
	if descriptor in preparedItemInstances:
		item = Util.dictPop(preparedItemInstances, descriptor)
		
		prepareInstance(descriptor)
	else:
		item = descriptor.instantiate()
		
		
	call_deferred("emit_signal", "item_instantiated_deferred", item)
	return item


func instantiateItem_pooled(descriptorOrName):
	var item
	if descriptorOrName is String:
		item = items[descriptorOrName].instantiate_pooled()
	else:
		item = descriptorOrName.instantiate_pooled()
	
	call_deferred("emit_signal", "item_instantiated_deferred", item)
	return item

func instantiateItemFromIndex(index):
	return instantiateItem(getDescriptorFromIndex(index))

func getItemIndex(item) -> int:
	if item is String:
		return items[item].itemIndex
	elif item is Item:
		return item.descriptor.itemIndex
	else:
		return item.itemIndex

func getDescriptorFromIndex(index: int) -> ItemDescriptor:
	return descriptorList[index]



func getOwnedItems():
	var owned = Game.PLAYER.INVENTORY.getItemsAndGems()
	owned.append_array(Game.STORAGEBOX.getItemsAndGems())
	if (Game.draggedItem and 
		not Game.draggedItem.sold and 
		not Game.draggedItem in owned):
		owned.push_back(Game.draggedItem)
	return owned

func getOwnedAndReservedItems():
	var owned = getOwnedItems()
	owned.append_array(Game.shopSceneNode.getReservedItemsNoNull())
	return owned

func getInventoryStorageShopItems():
	return (Game.PLAYER.INVENTORY.getItemsAndGems() + 
			Game.STORAGEBOX.getItemsAndGems() + 
			Game.shopSceneNode.getItemsNoNull())






func isItemOnScreen(item) -> bool:
	var descriptor
	if item is String:
		descriptor = getDescriptor(item)
	else:
		descriptor = item
	
	return descriptor in ownableItems
















func isItemStashed(descriptor: ItemDescriptor) -> bool:
	var stashed = Game.shopSceneNode.getStashedReservedItems()
	return stashed != null and descriptor.itemIndex in stashed

func getItemsInInventoryOfType(descriptor: ItemDescriptor) -> Array:
	if not descriptor in ownableItems:
		return []
	
	var inInventory = []
	for item in ownableItems[descriptor]:
		if (item.ownerType == Item.Owner.PlayerInventory or 
			item.ownerType == Item.Owner.Socket):
			inInventory.push_back(item)
	return inInventory

func countItemsInInventoryOfType(descriptor) -> int:
	if not descriptor in ownableItems:
		return 0
	
	var count = 0
	for item in ownableItems[descriptor]:
		if (item.ownerType == Item.Owner.PlayerInventory or 
			item.ownerType == Item.Owner.Socket):
			count += 1
	return count

func countPlacedItemsInInventoryOfType(descriptor) -> int:
	if not descriptor in ownableItems:
		return 0
	
	var count = 0
	for item in ownableItems[descriptor]:
		if ((item.placed and item.ownerType == Item.Owner.PlayerInventory) or 
			item.ownerType == Item.Owner.Socket):
			count += 1
	return count

func countOwnedItemsOfType(descriptor) -> int:
	if not descriptor in ownableItems:
		return 0
	
	var count = 0
	for item in ownableItems[descriptor]:
		if (item.ownerType == Item.Owner.PlayerInventory or 
			item.ownerType == Item.Owner.Socket or 
			item.ownerType == Item.Owner.PlayerStorageBox):
			count += 1
	return count

func getOwnedCounter() -> Dictionary:
	var counter = {}
	for descriptor in ownableItems:
		var count = countOwnedItemsOfType(descriptor)
		if count > 0:
			counter[descriptor] = count
		
	return counter

func isItemInInventory(descriptor) -> bool:
	if not descriptor in ownableItems:
		return false
	
	for item in ownableItems[descriptor]:
		if (item.ownerType == Item.Owner.PlayerInventory or 
			item.ownerType == Item.Owner.Socket):
			return true
	
	return false

func isItemInInventory_opponent(descriptor) -> bool:
	return descriptor in opponentItems

func getItemsOnScreenOfType(descriptor) -> Array:
	return ownableItems.get(descriptor, [])



















func isItemOwned(descriptor) -> bool:
	if not descriptor in ownableItems:
		return false
	
	for item in ownableItems[descriptor]:
		if (item.ownerType == Item.Owner.PlayerInventory or 
			item.ownerType == Item.Owner.PlayerStorageBox or 
			item.ownerType == Item.Owner.Socket):
			return true
	
	return false


func isItemOwnedAndWillNotBeConsumed(descriptor) -> bool:
	if not descriptor in ownableItems:
		return false
	
	for item in ownableItems[descriptor]:
		if ((item.ownerType == Item.Owner.PlayerInventory or 
			item.ownerType == Item.Owner.PlayerStorageBox or 
			item.ownerType == Item.Owner.Socket) and 
			not item.willBeConsumed):
			return true
	
	return false

func getItemsInInventoryOfType_opponent(descriptor) -> Array:
	return opponentItems.get(descriptor, [])

func countItemsInInventoryOfType_opponent(descriptor) -> int:
	return opponentItems.get(descriptor, []).size()

func getGemIndex(gem):
	
	return gemIndex[gem.getName()]


func getGemForIndex(index) -> ItemDescriptor:
	return gemList[index]

func instanciateGemFromIndex(index):
	return getGemForIndex(index).instantiate()

func getNumSockets(itemIndex):
	return numSockets[itemIndex]


func generateItem(item):
	var generatedItem = instantiateItem(item)
	Game.incrementItemStatistic(Game.ItemStatistic.Acquired, 
		generatedItem.descriptor)
	
	return generatedItem

func generateAndStorageItem(item, spawnPos: Vector2, 
	targetPos: Vector2 = Game.STORAGEBOX.center + Util.randInBox(100, 100)):
	
	var generatedItem = generateItem(item)
	Game.playerNode.add_child(generatedItem)
	generatedItem.global_position = spawnPos
	generatedItem.pushToStorage(targetPos)
	return generatedItem











func countItems():
	itemCounter.clear()
	for item in getOwnedAndReservedItems():
		Util.dictAdd(itemCounter, item.descriptor, 1)
		if item.descriptor.baseIngredients:
			Util.dictAddDict(itemCounter, item.descriptor.baseIngredients.dict)
	
	
	missingCrossbladeIngredients = Counter.new().fromCounter(crossbladesDescriptor.baseIngredients)
	var ingredientsInInventory = getReleventIngredients(
		Game.PLAYER.INVENTORY.getItems(), crossbladesDescriptor)
	var ingredientsInStorage = getReleventIngredients(
		Game.STORAGEBOX.getItems(), crossbladesDescriptor)

	ingredientsInInventory.addCounter(ingredientsInStorage)
	var numBaseIngredients = missingCrossbladeIngredients.countAll()
	missingCrossbladeIngredients.removeCounter(ingredientsInInventory)
	var numMissingIngredients = missingCrossbladeIngredients.countAll()

	
	recipeIngredientsWeights.clear()

	for item in missingCrossbladeIngredients.dict:
		var completion = 1.0 - numMissingIngredients / float(numBaseIngredients)
		
		if completion > COMPLETION_THRESHOLD:
			recipeIngredientsWeights[item] = 1.0 + COMPLETION_WEIGHT * (completion - COMPLETION_THRESHOLD)
	
	emit_signal("items_counted")
	





func getInventoryAsDict() -> Dictionary:
	var dict = Dictionary()
	for item in Game.PLAYER.INVENTORY.getItemsAndGems():
		Util.dictAppend(dict, item.descriptor, item)
	return dict


func getRandomDescriptor():
	return Util.pickRandomElement(descriptorList)

func getRandomBagDescriptor():
	return Util.pickRandomElement(shopBags)

var weightFactor = 1.0
var weightBonus = 0.0

func addWeight(weight):
	weightBonus += weight

func multiplyWeight(factor):
	weightFactor *= factor

func randomItemOfRarity(rarity, excluded: Array, 
	encountered: Array, numRolls: int):
	
	var forClass = Game.curClass
	if not Game.isClassUnlocked():
		forClass = Game.Classes.Ranger
	
	var possibleItems = curShopItems[rarity].duplicate()
	
	possibleItems = Util.subtractArr(possibleItems, excluded)
	
	var uniqueDescriptors = []
	
	if Game.state == Game.State.Shop:
		var otherItems = getOwnedAndReservedItems()
		for item in otherItems:
			if item.descriptor.canOnlyExistOnce():
				uniqueDescriptors.push_back(item.descriptor)
			
			if item.descriptor in spiritCompanionDescriptors:
				if not isItemOwned(spiritBellsDescriptor):
					uniqueDescriptors.append_array(spiritCompanionDescriptors)
		
		
		for descriptor in excluded:
			if descriptor in spiritCompanionDescriptors:
				if not isItemOwned(spiritBellsDescriptor):
					uniqueDescriptors.append_array(spiritCompanionDescriptors)
		
		possibleItems = Util.subtractArr(possibleItems, uniqueDescriptors)
	
	if possibleItems.empty():
		possibleItems = excluded
	
	var weights = Array()
	for item in possibleItems:
		var thresholdWeight = item.getThresholdWeight(itemCounter)
		var weight = item.getWeight()
		weight *= thresholdWeight
		weight *= getRecipeCompletionWeight(item)
		var lastEncounter = numRolls - encountered[item.itemIndex]
		if encountered[item.itemIndex] == NOT_ENCOUNTERED:
			weight *= 2.3
		elif lastEncounter > 5 and thresholdWeight >= 1.0:
			weight *= 1.4
		elif lastEncounter < 3 and not item.isBag():
			weight *= 0.1
		
		
		weightBonus = weight
		weightFactor = 1.0
		emit_signal("pre_item_roll", item)
		
		weights.push_back(weightBonus * weightFactor)
	
	Util.eassert(weights.size() == possibleItems.size())
	var index = randomItemWeightedBag.rollOnce(weights)
	var descriptor = possibleItems[index]
	
	emit_signal("item_rolled", descriptor)
	
	return instantiateItem(descriptor)

func randomBagOfRarity(rarity, excludeDescriptors = []):
	
	if bagsForRarity[rarity][Game.curClass].empty():
		rarity = Item.Rarity.Common

	var descriptor = Util.pickRandomElement(bagsForRarity[rarity][Game.curClass])
	for i in 3:
		if not excludeDescriptors.has(descriptor):
			break
		descriptor = Util.pickRandomElement(bagsForRarity[rarity][Game.curClass])

	return instantiateItem(descriptor)

func randomNonBagOfRarity(rarity, excludeDescriptors: Array, 
	encountered: Array, numRolls: int):

	
	var forClass = Game.curClass
	if not Game.isClassUnlocked():
		forClass = Game.Classes.Ranger

	for bag in bagsForRarity[rarity][forClass]:
		excludeDescriptors.push_back(bag)

	return randomItemOfRarity(rarity, excludeDescriptors, 
		encountered, numRolls)

func randomWeaponOfRarity(rarity, excludeDescriptors: Array, 
	encountered: Array, numRolls: int):

	var forClass = Game.curClass
	if not Game.isClassUnlocked():
		forClass = Game.Classes.Ranger

	var possibleItems = curShopItems[rarity]

	for item in possibleItems:
		if not item.isStartingWeapon():
			excludeDescriptors.push_back(item)

	

	return randomItemOfRarity(rarity, excludeDescriptors, 
		encountered, numRolls)

func getRandomTreasureDescriptor(maxPrice = 9000) -> ItemDescriptor:
	var onScreenUniques = getOnScreenUniques()
	var weights = Array()
	for item in uniqueItems:
		var weight
		if (item.getPrice() > maxPrice or 
			Game.curRound < item.earliestRound or 
			Game.curRound > item.latestRound or 
			item == classBadges[Game.curClass] or 
			item in onScreenUniques or 
			(item == puzzleBadgeDescriptor and isItemOwned(puzzleboxDescriptor))):
			weight = 0
		else:
			weight = item.getWeight()

		weights.push_back(weight)

	var index = randomItemWeightedBag.rollOnce(weights)
	return uniqueItems[index]

func getRandomUnique() -> Item:
	return instantiateItem(getRandomTreasureDescriptor())

	

func getRandomRarity(_rarityOdds: Array):
	return rarityWeightedBag.rollOnce(_rarityOdds)

func getRandomItemWithRarityOdds(_rarityOdds: Array) -> ItemDescriptor:
	var rarity = getRandomRarity(_rarityOdds)
	var possibleItems = []
	var forClass = Game.curClass
	if not Game.isClassUnlocked():
		forClass = Game.Classes.Ranger

	for descriptor in descriptorList:
		if descriptor.rarity == rarity and descriptor.isAvailableFor(forClass):
			possibleItems.push_back(descriptor)
		
	
	return Util.pickRandomElement(possibleItems)

const validatorHeader = "extends Object"
const validatorFormatLine = "var {varName} = \"{hash}\""
var validatedResources = {
	"items": "res://Sheets/CSV/ItemData_e.csv", 
	"ranger": "res://CharacterClasses/Ranger.tres", 
	"reaper": "res://CharacterClasses/Reaper.tres", 
	"berserker": "res://CharacterClasses/Berserker.tres", 
	"pyromancer": "res://CharacterClasses/Pyromancer.tres"
}
var sheetKey = PoolByteArray()


func validateResources():
	for i in 32:
		sheetKey.append(i)
	if Game.EDITOR:
		var file1: File = File.new()
		file1.open("res://Sheets/CSV/ItemData.csv", File.READ)
		var data = file1.get_as_text()
		var file2: = File.new()
		file1.open_encrypted("res://Sheets/CSV/ItemData_e.csv", File.WRITE, sheetKey)
		file1.store_string(data)
		file1.close()
		file2.close()
	
	
	var file = File.new()

	if Game.EDITOR:
		file.open("res://Utility/DataValidator.gd", File.WRITE)
		file.store_line(validatorHeader)
		for res in validatedResources:
			var md5 = file.get_md5(validatedResources[res])
			file.store_line(validatorFormatLine.format({
				"varName": res, 
				"hash": md5
				}))
		file.close()
	else:
		var validator = load("res://Utility/DataValidator.gd").new()
		for res in validatedResources:
			var md5 = file.get_md5(validatedResources[res])
			if validator.get(res) != md5:
				print("loading error 2")
				get_tree().quit()
		validator.free()



func _ready() -> void :
	pause_mode = Node.PAUSE_MODE_PROCESS
	validateResources()

	Game.connect("character_changed", self, "onCharacterChanged")
	Game.connect("loadout_changed", self, "onLoadoutChanged")

	if Game.loadExclusiveContent():
		for locale in Game.locales.values():
			TranslationServer.add_translation(load("res://Sheets/CSV/ExclusiveItems." + locale + ".translation"))

	if Game.loadUnreleasedContent():
		for locale in Game.locales.values():
			TranslationServer.add_translation(load("res://Sheets/CSV/Unreleased." + locale + ".translation"))

	for rarity in Item.Rarity:
		var arr1 = []
		var arr2 = []
		for classI in Game.getNumClasses():
			arr1.push_back([])
			arr2.push_back([])

		bagsForRarity.push_back(arr2)
		gemsForRarity.push_back([])
		foodsForRarity.push_back([])

	for classI in Game.getNumClasses():
		classSpecificItems.push_back([])
		subclassUniques.push_back({})
	
	for type in Item.Type:
		if type.to_lower() in Util.icons:
			typesWithIcons.push_back(type)
	
	if Game.PLAYTEST and SteamHelper.STEAMDECK and OS.is_debug_build():
		table = Table.new().loadFromCsv("res://Sheets/CSV/ItemData.csv")
	else:
		table = Table.new().loadFromCsv("res://Sheets/CSV/ItemData_e.csv", sheetKey)
	
	var dir = Directory.new()
	
	for line in table.countRows() - 1:
		
		var item = ItemDescriptor.new()
		
		var itemName = table.getStr("name", line)
		item.identifier = itemName
		
		var itemSet = table.getStr("demo", line)
		if itemSet == "no":
			item.releaseState = ItemDescriptor.ReleaseState.Full
		elif itemSet == "nooo":
			item.releaseState = ItemDescriptor.ReleaseState.Unreleased
		else:
			item.releaseState = ItemDescriptor.ReleaseState.Demo
		
		
			
			
			
			
			
		
		var mainType = table.getStr("type", line)
		if mainType == "Melee Weapon":
			item.types.push_back(Item.Type.Weapon)
			call_deferred("addItemType", item, Item.Type.Melee)
		elif mainType == "Ranged Weapon":
			item.types.push_back(Item.Type.Weapon)
			call_deferred("addItemType", item, Item.Type.Ranged)
			
		else:
			item.types.push_back(table.getEnu("type", Item.Type, line))
		
		var extraTypes = table.getStr("extraTypes", line).replace(" ", "").split(",")
		for type in extraTypes:
			if type != "":
				item.types.push_back(Item.Type[type])
		
		var itemNameNoSpaces = itemName.replace(" ", "")
		var scenePath = "Items/" + itemNameNoSpaces + ".tscn"

		if item.types[0] == Item.Type.Gem:
			scenePath = "Items/Gems/" + itemNameNoSpaces + ".tscn"
			

		if dir.file_exists(scenePath):
			item.scene = load(scenePath)
		else:
			if Game.loadExclusiveContent():
				if item.types[0] == Item.Type.ChessPiece:
					scenePath = "Items/Exclusive/Chess/" + itemNameNoSpaces + ".tscn"
				else:
					scenePath = "Items/Exclusive/" + itemNameNoSpaces + ".tscn"
				if dir.file_exists(scenePath):
					item.scene = load(scenePath)
					
				elif Game.loadUnreleasedContent():
					scenePath = "Items/Exclusive/Unreleased/" + itemNameNoSpaces + ".tscn"
					item.scene = load(scenePath)

		var aniPath = "Items/Animations/" + itemNameNoSpaces + "Animation.tscn"
		if dir.file_exists(aniPath):
			item.animationScene = load(aniPath)
		else:
			if Game.loadExclusiveContent():
				aniPath = "Items/Exclusive/Animations/" + itemNameNoSpaces + "Animation.tscn"
				if dir.file_exists(aniPath):
					item.animationScene = load(aniPath)
				elif Game.loadUnreleasedContent():
					aniPath = "Items/Exclusive/Unreleased/" + itemNameNoSpaces + "Animation.tscn"
					if dir.file_exists(aniPath):
						item.animationScene = load(aniPath)
		
		var shop = table.getStr("shop", line)
		var classes = ItemDescriptor.StuffedClasses.Undefined
		item.version = Game.versionToInt(table.getStr("version", line))
		
		var loadItem = item.isReleased()
		
		




		
		if loadItem:
			if item.isWeapon() or item.types[0] == Item.Type.Potion:
				if not item.animationScene:
					Util.eprint(itemName, " has no animation")
			
			table.fillList(item, ["minDam", "maxDam", "price", 
				"accuracy", "chance", "chance2", "shopChance", "staminaCost", "block", 
				"threshold", "weight", "earliestRound", "latestRound"], line)
			
			var cds = table.getStr("cd", line).replace(" ", "").split(",")
			if cds.size() > 0:
				item.cd = float(cds[0])
			for i in range(1, cds.size()):
				item.extraCds.push_back(float(cds[i]))
			
			item.rarity = table.getEnu("rarity", Item.Rarity, line)
			
			var requiredItemStr = table.getStr("requires", line)
			if requiredItemStr != "":
				item.requiredItem = getDescriptor(requiredItemStr)
			
			if item.isBag() and item.rarity != Item.Rarity.Unique:
				shopBags.push_back(item)
			
			item.tags = table.getFlags("tags", Item.Tag, line)
			item.material = table.getEnu("material", Item.Mat, line, Item.Mat.Default)
			item.physics = table.getEnu("physics", Item.Physics, line, Item.Physics.Default)
			var textEffect = table.getEnu("textEffect", ItemToolTip.TextEffect, line, ItemToolTip.TextEffect.NotSet)
			if textEffect == ItemToolTip.TextEffect.NotSet:
				item.textEffect = ItemToolTip.TextEffect.None
				
				for type in item.types:
					if type in typeToTextEffect:
						item.textEffect = typeToTextEffect[type]
						break
			else:
				item.textEffect = textEffect
			
			var paramI = 0
			for colI in NUM_PARAMS:
				var col = "p" + str(colI + 1)
				var colStr = table.getStr(col, line)
				if "," in colStr:
					var paramSubList = colStr.split(",")
					for split in paramSubList:
						var split2 = split.split(":")
						var paramVal = float(split2[0])
						item.addNamedParam(split2[1], paramVal)
						
						item.params.push_back(paramVal)
						paramI += 1
				else:
					var paramVal = table.getFloat(col, line, 0)
					var paramName = table.getParamName(col, line)
					if paramName != "":
						item.addNamedParam(paramName, paramVal)
					
					item.params.push_back(paramVal)
					paramI += 1
			
			item.gainedStacks = table.getFlags("gain", Item.Stack, line)
			item.removedStacks = table.getFlags("remove", Item.Stack, line)
			item.usedStacks = table.getFlags("use", Item.Stack, line)
			
			if table.getStr("canActivate", line) == "no":
				item.canActivate = false
			
			if item.isBag():
				item.activationAni = Item.ActivationAni.Scale
			elif item.hasType(Item.Type.Potion):
				item.activationAni = Item.ActivationAni.Potion
			else:
				item.activationAni = table.getEnu("animation", Item.ActivationAni, line, 
					Item.ActivationAni.Jump)
			
			if shop == "":
				classes = ItemDescriptor.StuffedClasses.Neutral
				for classI in Game.getNumClasses():
					addToShop(classI, item)
			elif shop == "no":
				classes = ItemDescriptor.StuffedClasses.None
			elif shop == "unique":
				classes = ItemDescriptor.StuffedClasses.Neutral
				uniqueItems.push_back(item)
				item.randomUniquePool = true
			elif shop == "special":
				
				classes = ItemDescriptor.StuffedClasses.Neutral
			elif ">" in shop:
				var parts = shop.split(">")
				var className = parts[0]
				var subclassName = parts[1]
				
				var classI = Game.getClassEnum()[className]
				subclassUniques[classI][subclassName] = item
				item.startsSubclass = subclassName
				classes = ItemDescriptor.stuffClassIndex(classI)
			
			elif item.hasType(Item.Type.Skill):
				var split: Array = shop.split(" ")
				var classList = split[0].split(",")
				classes = ItemDescriptor.StuffedClasses.None
				for className in classList:
					classes += ItemDescriptor.StuffedClasses[className]
				var rounds = split[1].split(",")
				
				for skillRound in rounds:
					skills[int(skillRound) - 1].push_back(item)
					
					
					if int(skillRound) == 1:
						item.appearRounds.push_back(Game.SKILL_ROUND1)
					else:
						item.appearRounds.push_back(Game.SKILL_ROUND2)
				
			else:
				var classI = Game.getClassEnum()[shop]
				classes = ItemDescriptor.stuffClassIndex(classI)
				
				classSpecificItems[classI].push_back(item)
				addToShop(classI, item)
			
			if item.hasType(Item.Type.Food):
				foodsForRarity[item.rarity].push_back(item)
			
			if item.hasTag(Item.Tag.Staff):
				staffDescriptors.push_back(item)
		
		item.classes = classes
		
		items[itemName] = item
		var index = table.getInt("id", line)
		item.itemIndex = index

		item.sheetIndex = sheetList.size()
		sheetList.push_back(item)
		if item.types[0] == Item.Type.Gem:
			sheetList.push_back(item)
			sheetList.push_back(item)

	descriptorList.resize(getNumItems())
	for item in items.values():
		if descriptorList[item.itemIndex] != null:
			print("duplicate item index ", item.itemIndex)
		descriptorList[item.itemIndex] = item

	for itemName in items:
		if items[itemName].types[0] == Item.Type.Gem:
			gemIndex[itemName] = gemList.size()
			gemList.push_back(items[itemName])

	numSockets.resize(getNumItems())
	for item in items.values():
		if item.scene:
			var sockets = 0
			var state: SceneState = item.scene.get_state()
			for i in state.get_node_count():
				if state.get_node_name(i).begins_with("GemSocket"):
					sockets += 1
			numSockets[item.itemIndex] = sockets
		else:
			numSockets[item.itemIndex] = 0
			Util.eprint(item.getName(), " has no scene")

















	
	boxOfRichesDescriptor = getDescriptor("Box of Riches")
	deckOfCardsDescriptor = getDescriptor("Deck of Cards")
	crossbladesDescriptor = getDescriptor("Crossblades")
	platinCardDescriptor = getDescriptor("Platin Customer Card")
	customerCardDescriptor = getDescriptor("Customer Card")
	staminaSackDescriptor = getDescriptor("Stamina Sack")
	
	presentDescriptor = getDescriptor("Present")
	flameDescriptor = getDescriptor("Flame")
	forgingHammerDescriptor = getDescriptor("Forging Hammer")
	amuletDescriptor = getDescriptor("Amulet Unidentified")
	amuletOfFeastingDescriptor = getDescriptor("Amulet of Feasting")
	for amulet in amuletNames:
		amulets.push_back(getDescriptor(amulet))
	
	starOfCourageDescriptor = getDescriptor("Star of Courage")
	toolboxDescriptor = getDescriptor("Toolbox")
	stableRecombobulatorDescriptor = getDescriptor("Stable Recombobulator")
	unstableRecombobulatorDescriptor = getDescriptor("Unstable Recombobulator")
	extraBagsDescriptor = getDescriptor("Extra Bags")
	
	classBadges[Game.Classes.Ranger] = getDescriptor("Leaf Badge")
	classBadges[Game.Classes.Reaper] = getDescriptor("Skull Badge")
	classBadges[Game.Classes.Berserker] = getDescriptor("Wolf Badge")
	classBadges[Game.Classes.Pyromancer] = getDescriptor("Flame Badge")
	classBadges[Game.Classes_Full.Mage] = getDescriptor("Magic Badge")
	classBadges[Game.Classes_Full.Adventurer] = getDescriptor("Twine Badge")
	classBadges[Game.Classes_Full.Engineer] = getDescriptor("Cog Badge")
	
	rainbowBadgeDescriptor = getDescriptor("Rainbow Badge")
	stoneBadgeDescriptor = getDescriptor("Stone Badge")
	
	spiritCompanionDescriptors.push_back(getDescriptor("Cat Spirit"))
	spiritCompanionDescriptors.push_back(getDescriptor("Badger Spirit"))
	spiritCompanionDescriptors.push_back(getDescriptor("Owl Spirit"))
	spiritBellsDescriptor = getDescriptor("Spirit Bells")
	bagOfGivingDescriptor = getDescriptor("Bag of Giving")
	chessboardDescriptor = getDescriptor("Chess Board")
	
	scrolls.push_back(getDescriptor("Spell Scroll Ice"))
	scrolls.push_back(getDescriptor("Spell Scroll Nature"))
	scrolls.push_back(getDescriptor("Spell Scroll Light"))
	scrolls.push_back(getDescriptor("Spell Scroll Dark"))
	
	books.push_back(getDescriptor("Book of Ice"))
	books.push_back(getDescriptor("Book of Nature"))
	books.push_back(getDescriptor("Book of Light"))
	books.push_back(getDescriptor("Book of Darkness"))
	



	
	snowmanDescriptor = getDescriptor("Snowman")
	uniquelyUniqueDescriptor = getDescriptor("Uniquely Unique")
	bagtacularDescriptor = getDescriptor("Bagtacular")
	justStatsDescriptor = getDescriptor("Just Stats")
	moreStatsDescriptor = getDescriptor("More Stats")
	unidentifiedSkillDescriptor = getDescriptor("Unidentified Skill")
	nonGeneratableSkills[justStatsDescriptor] = true
	nonGeneratableSkills[moreStatsDescriptor] = true
	nonGeneratableSkills[unidentifiedSkillDescriptor] = true
	
	digDeeperDescriptor = getDescriptor("Dig Deeper")
	puzzleboxDescriptor = getDescriptor("Puzzlebox")
	puzzleBadgeDescriptor = getDescriptor("Puzzle Badge")
	sewingCaseDescriptor = getDescriptor("Sewing Case")
	twineDescriptor = getDescriptor("Twine")
	arcaneIntellectDescriptor = getDescriptor("Arcane Intellect")
	fedoraDescriptor = getDescriptor("Fedora")
	piggyOfRichesDescriptor = getDescriptor("Piggy of Riches")
	
	for puzzleBag in ["L", "S", "Z", "T", "J"]:
		puzzleBags.push_back(getDescriptor("Puzzlebag " + puzzleBag))
	
	piggies[piggyOfRichesDescriptor] = true
	piggies[getDescriptor("Piggybank")] = true
	piggies[getDescriptor("Lucky Piggy")] = true
	
	batteryDescriptor = getDescriptor("Battery")
	coilDescriptor = getDescriptor("Coil")
	chargeSplitterDescriptor = getDescriptor("Charge Splitter")
	manaCrystalDescriptor = getDescriptor("Mana Crystal")
	lightningStaffDescriptor = getDescriptor("Lightning Staff")
	boxofCogsDescriptor = getDescriptor("Engineer Bag 2")
	cogDescriptor = getDescriptor("Cog")
	generatorDescriptor = getDescriptor("Generator")
	cogBadgeDescriptor = getDescriptor("Cog Badge")
	contraptronDescriptor = getDescriptor("Con-Trap-Tron")
	bloodAmuletDescriptor = getDescriptor("Blood Amulet")
	magicRingDescriptor = getDescriptor("Magic Ring")
	superiorRingDescriptor = getDescriptor("Superior Ring")
	hyperCubeDescriptor = getDescriptor("Hypercube")
	hyperCubes.push_back(getDescriptor("Chrome Cube"))
	hyperCubes.push_back(getDescriptor("Gold Cube"))
	hyperCubes.push_back(getDescriptor("Plastic Cube"))
	hyperCubes.push_back(getDescriptor("Bismuth Cube"))
	
	
	for line in table.countRows() - 1:
		var index = table.getInt("id", line)
		var item = descriptorList[index]
		
		if not item.isReleased():
			continue
		
		var gateItemStr = table.getStr("gateItem", line)
		if gateItemStr != "":
			item.gateItem = getDescriptor(gateItemStr)
			item.gateItem.gatedItems.push_back(item)
		
		if item.types[0] == Item.Type.Gem:
			if gateItemStr == "Box of Riches":
				gemsForRarity[item.rarity].push_back(item)
		
		var recipesStr = table.getStr("recipes", line)
		if recipesStr != "":
			parseRecipe(item, recipesStr)
		
		var appropriatingItems = table.getStr("appropriated", line)
		if appropriatingItems != "":
			parseAppropriatingItems(item, appropriatingItems)
		
	
	calcRecipeTrees()
	
	if Game.loadExclusiveContent():
		addCauldronRecipes()
	
	calcClassAvailability()
	
	for line in table.countRows() - 1:
		var index = table.getInt("id", line)
		var item = descriptorList[index]
		
		if not item.isReleased():
			continue
		
		var classOverride = table.getEnuStuffed("class_override", ItemDescriptor.StuffedClasses, line)
		if classOverride != null:
			item.classes = classOverride
	
	
	table = null
	
	initDescriptionKeys()
	detectMentionedStacks()
	
	for recipe in forgingHammerDescriptor.recipesAsIngredient:
		var newRecipe: = Recipe.new()
		newRecipe.init(recipe.baseItem, [toolboxDescriptor], 
			[true], recipe.fusedItem)
	
	var bloodAmulet = getDescriptor("Blood Amulet")
	var manaOrb = getDescriptor("Mana Orb")
	var holyArmor = getDescriptor("Holy Armor")
	
	var magicCollar = getDescriptor("Magic Collar")
	var vampiricCollar = getDescriptor("Vampiric Collar")
	var holyCollar = getDescriptor("Holy Collar")
	
	Recipe.new().init(magicCollar, [bloodAmulet], [true], vampiricCollar)
	Recipe.new().init(holyCollar, [bloodAmulet], [true], vampiricCollar)
	Recipe.new().init(holyCollar, [manaOrb], [true], magicCollar)
	Recipe.new().init(vampiricCollar, [manaOrb], [true], magicCollar)
	Recipe.new().init(magicCollar, [holyArmor], [true], holyCollar)
	Recipe.new().init(vampiricCollar, [holyArmor], [true], holyCollar)
	
	for descriptor in descriptorList:
		if descriptor.scene == null: continue
		
		if descriptor.rarity == Item.Rarity.Common:
			prepareInstance(descriptor, 3)
		elif descriptor.rarity < Item.Rarity.Unique:
			prepareInstance(descriptor, 2)
		else:
			prepareInstance(descriptor, 1)
		
		if descriptor.isBag() and descriptor.rarity < Item.Rarity.Unique:
			prepareInstance(descriptor, 8)














	





























func addToShop(classI, item):
	
	if item.types[0] == Item.Type.Bag:
		bagsForRarity[item.rarity][classI].push_back(item)
	
	item.shopItem = true
	
























var itemPoolingIndex: = 0

func _process(delta):
	if itemPoolingIndex < descriptorList.size() - 1:
		var scene = descriptorList[itemPoolingIndex].scene
		if scene != null:
			ObjectPool.prepare(scene, 2)
		itemPoolingIndex += 1
	
	if (Game.state == Game.State.Shop or 
		Game.buildHistory.isOpen):
		call_deferred("prepareItemInstances")

func addItemType(descriptor, type: int):
	descriptor.types.push_back(type)

func parseRecipe(baseItemDescriptor, recipesStr):
	var recipes = recipesStr.split(",")
	for recipeStr in recipes:
		var recipe = Recipe.new().fromString(baseItemDescriptor, recipeStr)

func addCauldronRecipes():
	var cauldronDescriptor = getDescriptor("Cauldron")
	for itemName in items:
		var potionDescriptor = items[itemName]
		if potionDescriptor.types[0] == Item.Type.Potion:
			var strongName = "Strong " + itemName
			if strongName in items:
				
				var strongPotion = items[strongName]
				var recipe = Recipe.new().init(
					potionDescriptor, [cauldronDescriptor], [true], strongPotion)


func calcClassAvailability():
	
	var craftingDepthBuckets = []
	for itemName in items:
		var descriptor = items[itemName]
		var depth = descriptor.getCraftingDepth()
		if craftingDepthBuckets.size() - 1 < depth:
			craftingDepthBuckets.resize(depth + 1)
		
		if craftingDepthBuckets[depth] == null:
			craftingDepthBuckets[depth] = []
		craftingDepthBuckets[depth].push_back(descriptor)

	for i in craftingDepthBuckets.size():
		for descriptor in craftingDepthBuckets[i]:
			descriptor.calcClassAvailability()

	
	

	for itemName in items:
		var descriptor = items[itemName]
		if canBeGifted(descriptor):
			descriptor.addAppropriatingItem(presentDescriptor)
			descriptor.addAppropriatingItem(rainbowBadgeDescriptor)
			descriptor.addAppropriatingItem(stableRecombobulatorDescriptor)
			descriptor.addAppropriatingItem(bagOfGivingDescriptor)
			
	
		for classI in Game.Classes_Full.size():
			if descriptor.isAvailableFor(classI):
				if classBadges[classI] != null:
					descriptor.addAppropriatingItem(classBadges[classI])
	
	forgingHammerDescriptor.addAppropriatingItem(rainbowBadgeDescriptor)
	forgingHammerDescriptor.addAppropriatingItem(classBadges[Game.Classes.Berserker])
	forgingHammerDescriptor.addAppropriatingItem(bagOfGivingDescriptor)
	
	var furciferPrimeDescriptor = getDescriptor("Furcifer Prime")
	
	for itemName in items:
		var descriptor = items[itemName]
		if descriptor.hasType(Item.Type.Food) and descriptor.rarity <= Item.Rarity.Godly:
			descriptor.addAppropriatingItem(amuletOfFeastingDescriptor)
		
		if isAppropriatedByDigDeeper(descriptor):
			descriptor.addAppropriatingItem(digDeeperDescriptor)
		
		if descriptor.isCraftedItem():
			descriptor.addAppropriatingItem(furciferPrimeDescriptor)
	
	var rainbowPotion = getDescriptor("Rainbow Potion")
	for staff in staffDescriptors:
		staff.addAppropriatingItem(rainbowPotion)
	
	for i in craftingDepthBuckets.size():
		for descriptor in craftingDepthBuckets[i]:
			descriptor.calcAppropriation()
	
	call_deferred("ready_deferred")

func ready_deferred():
	Game.itemLibrary.connect("items_initialized", self, "addAppropriations")

func addAppropriations():
	var speakWithAnimalsDescr = getDescriptor("Speak with Animals")
	for petName in Game.itemLibrary.getInstance(speakWithAnimalsDescr).pets:
		getDescriptor(petName).addAppropriatingItem(speakWithAnimalsDescr)

func parseAppropriatingItems(item, line):
	var split = line.split(",")
	for itemName in split:
		itemName = itemName.strip_edges()
		item.appropriatingItems.push_back(items[itemName])
		

func initDescriptionKeys():
	for itemName in items:
		var item = items[itemName]
		if item.isGem():
			if itemName.ends_with("Ruby"):
				item.descriptionKey = "Ruby"
			elif itemName.ends_with("Sapphire"):
				item.descriptionKey = "Sapphire"
			elif itemName.ends_with("Emerald"):
				item.descriptionKey = "Emerald"
			elif itemName.ends_with("Topaz"):
				item.descriptionKey = "Topaz"
			elif itemName.ends_with("Amethyst"):
				item.descriptionKey = "Amethyst"

		if item.descriptionKey == "":
			item.descriptionKey = itemName


func detectMentionedStacks():
	
	var stackCmds = {}
	for stack in Game.stackIdentifiers:
		stackCmds[Game.stackIdentifiers[stack]] = "$" + stack
	
	var typeCmds = {}
	for type in typesWithIcons:
		typeCmds[type] = "$" + type
	
	for itemName in items:
		var item = items[itemName]
		var descr = item.getDescription()
		
		
		for stack in Game.stackIdentifiers.values():
			if Util.findWholeWord(descr, stackCmds[stack]) != - 1:
				item.mentionedStacks[stack] = true
		
		
		for type in typesWithIcons:
			if Util.findWholeWord(descr, typeCmds[type]) != - 1:
				item.mentionedTypes[Item.Type[type]] = true
	
		item.hasBattleRageEffect = (descr.find("$rage[") != - 1)

func calcRecipeTrees():
	for itemName in items:
		var item = items[itemName]
		if not item.originatingRecipes.empty():
			
			item.baseIngredients = getBaseIngredients(item)
			item.recipeTree = getRecipeTree(item)

			
			
			

func getGemOfRarity(rarity) -> ItemDescriptor:
	return Util.pickRandomElement(gemsForRarity[rarity])

func getFoodOfRarity(rarity) -> ItemDescriptor:
	match rarity:
		Item.Rarity.Epic:
			rarity += 1 if Util.flip() else - 1



	return Util.pickRandomElement(foodsForRarity[rarity])




func getNumInventoryUniques() -> int:
	var uniques = 0
	for item in Game.PLAYER.INVENTORY.getItemsAndGems():
		if item.descriptor.randomUniquePool:
			uniques += 1
	return uniques

func getOnScreenUniques(withShop = true):
	var uniques = {}
	for item in Game.PLAYER.INVENTORY.getItemsAndGems():
		if item.descriptor.randomUniquePool:
			uniques[item.descriptor] = 1
			
	for item in Game.STORAGEBOX.getItemsAndGems():
		if item.descriptor.randomUniquePool:
			uniques[item.descriptor] = 1
			
	if Game.draggedItem and Game.draggedItem.descriptor.randomUniquePool:
		uniques[Game.draggedItem.descriptor] = 1
		

	if withShop:
		for item in Game.shopSceneNode.getItemsNoNull():
			if item.descriptor.randomUniquePool:
				uniques[item.descriptor] = 1
				
	return uniques

func getNumUniques(withShop = true) -> int:
	var numUniques = 0
	var uniques = getOnScreenUniques(withShop)
	for unique in uniques:
		numUniques += uniques[unique]
	return numUniques




func getMaxUniques() -> int:
	var uniques = 1
	uniques += countItemsInInventoryOfType(platinCardDescriptor)
	if isItemInInventory(uniquelyUniqueDescriptor):
		uniques += int(uniquelyUniqueDescriptor.getP("uniquest"))
	if isItemInInventory(fedoraDescriptor):
		uniques += int(fedoraDescriptor.getP("uniquest"))



	if CustomRules.customRulesActive:
		uniques += CustomRules.getRuleValue(CustomRules.Rules.TreasureLimit)
	return uniques

func getTreasureCapacity() -> int:
	return getMaxUniques() - getNumUniques()

func getSubclassItemDescr(charClass):
	return subclassUniques[charClass].values()

func getPlayerSubclass():
	return getSubclass(Game.PLAYER.INVENTORY.getItems() + Game.STORAGEBOX.getItems())

func getSubclass(_items):
	for item in _items:
		if item.isSubclassItem():
			return item.descriptor.startsSubclass
	return ""

func getSubclassFromIndices(indices):
	for index in indices:
		var descr = getDescriptorFromIndex(index)
		if descr.isSubclassItem():
			return descr.startsSubclass
		elif descr in hyperCubes:
			return hyperCubeDescriptor.startsSubclass
	return ""



func canBeGifted(descriptor) -> bool:
	if descriptor.rarity == Item.Rarity.Unique:
		return false
	
	if descriptor.isTransient():
		return false
	
	for classI in Game.getNumClasses():
		if Game.isClassUnlocked(classI) and descriptor.isAvailableFor(classI):
			return true

	return false


enum Filter{
	Treasures = 1, 
	OtherClasses = 2, 
	AnyRarity = 4, 
	
	Gated = 8, 
	Crafted = 16, 
	Gems = 32, 
	Amulets = 64, 
	IgnoreWeight = 128, 
	OnlyCrafted = 256
}


func canBeGenerated(descriptor: ItemDescriptor, filters: int) -> bool:
	
	if not (filters & Filter.IgnoreWeight):
		var weight = descriptor.getThresholdWeight(itemCounter)
		
		if weight < 1 and not Util.flip(weight):
			
			return false
	
	
	if descriptor.isTransient():
		return false
	
	
	if descriptor.rarity == Item.Rarity.Unique:
		
		return false
	
	if not (filters & Filter.AnyRarity):
		if Game.shopSceneNode.getRarityOddsForCurRound()[descriptor.rarity] <= 0:
			return false
	
	
	if filters & Filter.OtherClasses:
		var ok = false
		for classI in Game.getNumClasses():
			if Game.isClassUnlocked(classI) and descriptor.isAvailableFor(classI):
				ok = true
				break
		if not ok:
			return false
	else:
		if not isAvailableForClasses(descriptor):
			return false
	
	
	if filters & Filter.OnlyCrafted:
		if not descriptor.isCraftedItem():
			return false
	elif not (filters & Filter.Crafted):
		if descriptor.isCraftedItem():
			if not (descriptor.isGem() and filters & Filter.Gems):
				return false
	
	
	if not (filters & Filter.Gated):
		if descriptor.isGatedItem():
			
			if not isItemOwned(descriptor.gateItem):
				
				if descriptor in amulets:
					if ( not (filters & Filter.Amulets)):
						return false
				else:
					return false
	else:
		
		if descriptor.hasType(Item.Type.Card) and not isItemOnScreen(deckOfCardsDescriptor):
			return false
		if descriptor.hasType(Item.Type.ChessPiece) and not isItemOnScreen(chessboardDescriptor):
			return false
	
	
	if descriptor.canOnlyExistOnce():
		if isItemOnScreen(descriptor) or isItemStashed(descriptor):
			return false
	
	
	if descriptor in spiritCompanionDescriptors:
		if not canHaveMoreCompanions():
			return false
		
	return true

func isAppropriatedByDigDeeper(descr):
	return descr.price >= 3 and descr.price <= 6

func isSpiritCompanion(descr: ItemDescriptor):
	return descr in spiritCompanionDescriptors

func canHaveMoreCompanions() -> bool:
	if isItemOwned(spiritBellsDescriptor):
		return true
	else:
		for spiritCompanion in spiritCompanionDescriptors:
			if isItemOnScreen(spiritCompanion):
				return false
	return true

func isRing(item) -> bool:
	return item.isA(magicRingDescriptor) or item.isA(superiorRingDescriptor)

func onOwnableItemAdded(item):



	Util.dictAppend(ownableItems, item.descriptor, item)
	
	
	

func onOwnableItemRemoved(item):
	Util.dictErase(ownableItems, item.descriptor, item)
	
	
	

func onOpponentItemAdded(item):
	Util.dictAppend(opponentItems, item.descriptor, item)
	

func cleanOwnableItems():
	for descriptor in ownableItems:
		for item in ownableItems[descriptor]:
			if not is_instance_valid(item) or item == null:
				print(descriptor.getName(), " leftover null instance")
				ownableItems[descriptor].erase(item)
				if ownableItems[descriptor].empty():
					ownableItems.erase(descriptor)
				return




func printOwnableItems():
	print("OWNABLE ITEMS")
	for descriptor in ownableItems:
		print(descriptor.getName(), ": ", ownableItems[descriptor].size())
		if descriptor.getName() == "Stone":
			for item in ownableItems[descriptor]:
				print("Stone owner: ", Util.enumToString(Item.Owner, item.ownerType))



func updateClass(triggeringItem = null):
	var check = true
	if triggeringItem:
		check = false
		if (triggeringItem.ownerType == Item.Owner.PlayerInventory or 
			(triggeringItem.ownerType == Item.Owner.PlayerStorageBox and 
				triggeringItem.descriptor == stoneBadgeDescriptor)):
			check = true

	if not check: return

	curShopItems.clear()
	





	curShopClasses = ItemDescriptor.stuffClassIndex(Game.curClass)
	for item in getOwnedItems():
		if item.ownerType == Item.Owner.PlayerInventory:
			for classI in classBadges:
				if item.descriptor == classBadges[classI]:
					curShopClasses |= ItemDescriptor.stuffClassIndex(classI)
					break
			if item.descriptor == rainbowBadgeDescriptor or item.descriptor == bagOfGivingDescriptor:
				curShopClasses |= ItemDescriptor.StuffedClasses.Neutral
		if item.descriptor == stoneBadgeDescriptor:
			curShopClasses &= ~ ItemDescriptor.stuffClassIndex(Game.curClass)
		
	
	for rarity in Item.Rarity:
		curShopItems.push_back([])

	for itemName in items:
		var descriptor = items[itemName]
		if descriptor.isShopItem():
			if isAvailableForClasses(descriptor):
				curShopItems[descriptor.rarity].push_back(descriptor)

func isAvailableForClasses(descriptor: ItemDescriptor):
	return (descriptor.classes == ItemDescriptor.StuffedClasses.Neutral or 
			descriptor.isAvailableForStuffed(curShopClasses))

func onCharacterChanged():
	updateClass()

func onLoadoutChanged():
	updateClass()

func canGetForgingHammer(inventoryDict: Dictionary) -> bool:
	var canAccessBerserkerItems = false
	
	if Game.curClass == Game.Classes.Berserker:
		canAccessBerserkerItems = not isItemOwned(stoneBadgeDescriptor)
	else:
		canAccessBerserkerItems = (
			classBadges[Game.Classes.Berserker] in inventoryDict or 
			rainbowBadgeDescriptor in inventoryDict or 
			bagOfGivingDescriptor in inventoryDict)
	
	if not canAccessBerserkerItems:
		return false
	
	if isItemOnScreen(forgingHammerDescriptor):
		return false
	
	if isItemOnScreen(toolboxDescriptor):
		return false
	
	return true

func getFullSkillPool() -> Array:
	var fullPool = []
	for roundI in [0, 1]:
		for skill in skills[roundI]:
			if not skill in nonGeneratableSkills:
				fullPool.push_back(skill)
	fullPool = Util.filterDuplicates(fullPool)
	return fullPool

func getSkillPool() -> Array:
	var skillPool = []
	var roundI = 0 if Game.curRound == Game.SKILL_ROUND1 else 1
	
	for skill in skills[roundI]:
		if ( not skill in nonGeneratableSkills and 
			skill.isAvailableFor(Game.curClass) and 
			not isItemOnScreen(skill)):
			
			if skill.requiredItem == null:
				skillPool.push_back(skill)
			elif (isItemOwnedAndWillNotBeConsumed(skill.requiredItem) or 
				skill.requiredItem in Game.itemsBeingCrafted):



				skillPool.push_back(skill)
	
	return skillPool

func getRandomSkills(num = 3) -> Array:
	var selectedSkills = []
	var skillPool = getSkillPool()
	var weights = Array()
	for item in skillPool:
		var weight = item.getWeight()
		
		if ( not item.isNeutral() and 
			item.classes != ItemDescriptor.stuffClassIndex(Game.curClass) and 
			Util.bitIncludes(curShopClasses, item.classes)):
				weight *= DUAL_CLASS_WEIGHT
			
		weights.push_back(weight)
	
	for i in num:
		var index = randomItemWeightedBag.rollOnce(weights)
		selectedSkills.push_back(skillPool[index])
		weights.remove(index)
		skillPool.remove(index)
		
	return selectedSkills





func getBaseIngredients(descriptor):
	var baseIngredients = Counter.new()
	addBaseIngredients(descriptor, baseIngredients)
	return baseIngredients

func addBaseIngredients(descriptor, ingredientCounter: Counter):
	if descriptor.originatingRecipes.empty():
		ingredientCounter.add(descriptor)
	else:
		var recipe = descriptor.originatingRecipes[0]
		for ingredient in recipe.getAllIngredients():
			if ingredient is ItemDescriptor:
				addBaseIngredients(ingredient, ingredientCounter)

func getRecipeTree(descriptor):
	var treeItems = Counter.new()
	addIngredients(descriptor, treeItems)
	treeItems.remove(descriptor)
	return treeItems

func addIngredients(descriptor, treeItems: Counter):
	if not descriptor.originatingRecipes.empty():
		var recipe = descriptor.originatingRecipes[0]
		for ingredient in recipe.getAllIngredients():
			if ingredient is ItemDescriptor:
				addIngredients(ingredient, treeItems)


func isInRecipeTree(item: ItemDescriptor, recipeItem: ItemDescriptor) -> bool:
	return recipeItem.recipeTree.has(item)

func getReleventIngredients(fromItems: Array, recipeItem: ItemDescriptor):
	var relevantIngredients = Counter.new()
	for item in fromItems:
		if isInRecipeTree(item.descriptor, recipeItem):
			addBaseIngredients(item.descriptor, relevantIngredients)
	return relevantIngredients

func getRecipeCompletionWeight(item: ItemDescriptor):
	if item in recipeIngredientsWeights:
		return recipeIngredientsWeights[item]
	else:
		return 1.0























func getShopItemsForClass(classI: int):
	var classItems = []
	for item in classSpecificItems[classI]:
		if item.getRarity() < Item.Rarity.Unique or not item.isBag():
			classItems.push_back(item)
	return classItems
