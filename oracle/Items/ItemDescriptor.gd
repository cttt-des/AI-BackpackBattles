extends Reference
class_name ItemDescriptor

enum StuffedClasses{
	Undefined = - 1, 
	None = 0, 
	Ranger = 1, 
	Reaper = 2, 
	Berserker = 4, 
	Pyromancer = 8, 
	Mage = 16, 
	Adventurer = 32, 
	Engineer = 64, 
	Neutral = 127
}

enum ReleaseState{
	Demo, 
	Full, 
	Unreleased
}

const PARAM_DELIMITER = "_"

var rarity = Item.Rarity.Common
var types: Array

var classes: int

var randomUniquePool = false
var material = Item.Mat.Default
var physics = Item.Physics.Default
var identifier: String
var minDam: int = 0
var maxDam: int = 0
var cd: float = 0.0
var extraCds: Array
var accuracy: float = 0.0
var chance: float = 0.0
var chance2: float = 0.0
var shopChance: float = 0.0
var tags = Item.Tag.None
var gainedStacks = Item.Stack.None
var removedStacks = Item.Stack.None
var usedStacks = Item.Stack.None
var params: Array
var namedParams: Dictionary
var sortedParamNames: Array
var paramBases: Dictionary
var paramBases_inverted: Dictionary
var descriptionKey: String
var searchDescription: String
var scene: PackedScene
var price: int
var staminaCost: float = 0.0
var block: int = 0
var animationScene
var recipes: = []
var recipesAsIngredient: = []

var originatingRecipes: = []
var baseIngredients: Counter
var recipeTree: Counter
var shopItem: = false
var gateItem = null
var gatedItems: = []
var requiredItem = null
var canActivate = true
var threshold: int = 100
var weight: float = 1.0
var startsSubclass: = ""
var itemIndex: int
var sheetIndex: int
var appropriatingItems = []
var mentionedStacks: Dictionary
var mentionedTypes: Dictionary
var hasBattleRageEffect: bool
var earliestRound: int = 4
var latestRound: int = 18
var appearRounds = []
var version: int
var releaseState: int
var activationAni: int = Item.ActivationAni.Jump
var textEffect: int

static func stuffClassIndex(classI):
	return 1 << classI

func instantiate():
	var item = scene.instance()
	item.descriptor = self
	return item

func instantiate_pooled():
	var item = ObjectPool.instance(scene)
	item.descriptor = self
	item.pooled = true
	return item

func addNamedParam(paramName: String, paramVal):
	namedParams[paramName] = paramVal
	var sortedPos = 0
	for i in sortedParamNames.size():
		if sortedParamNames[i].begins_with(paramName):
			sortedPos = i + 1
	sortedParamNames.insert(sortedPos, paramName)
	paramBases[paramName] = paramName.get_slice(PARAM_DELIMITER, 0)
	paramBases_inverted[paramBases[paramName]] = paramName

func getIndex() -> int:
	return itemIndex

func getName() -> String:
	return identifier

func getTranslatedName() -> String:
	var translated = Util.tra(getName() + "_NAME")
	if translated.ends_with("NAME"):
		return getName()
	else:
		return translated

func getRarity() -> int:
	return rarity

static func getTypeName(type) -> String:
	return Item.Type.keys()[type]

func getTranslatedTypeName(type) -> String:
	return Util.tra("TYPE_" + Item.Type.keys()[type] + "_NAME")

func getTranslatedTypes() -> Array:
	var tTypes = []
	for type in types:
		tTypes.push_back(getTranslatedTypeName(type))
	return tTypes

func getP(index) -> float:
	if typeof(index) == TYPE_INT:
		return params[index]
	else:
		return namedParams[index]

func hasParam(paramName: String) -> bool:
	return paramName in paramBases_inverted

func getShopChance() -> float:
	return shopChance

func getDescription() -> String:
	return Util.tra(descriptionKey + "_DESCR")

func isAvailableFor(classId: int) -> bool:
	return isAvailableForStuffed(stuffClassIndex(classId))


func isAvailableForStuffed(classId: int) -> bool:
	return bool(classes & classId)

func isNeutral() -> bool:
	return classes == StuffedClasses.Neutral

func isClassItem() -> bool:
	return (classes != StuffedClasses.Neutral and 
		classes != StuffedClasses.None)





		






func calcClassAvailability():
	if gateItem != null:
		if gateItem.classes == StuffedClasses.Undefined:
			Util.eprint(getName(), " classes are undefined. ")
		
		if classes == StuffedClasses.None:
			classes = gateItem.classes
	
	if not originatingRecipes.empty():
		if classes == StuffedClasses.Undefined:
			classes = StuffedClasses.None
		for recipe in originatingRecipes:
			var recipeClasses = StuffedClasses.Neutral
			for ingredient in recipe.getAllIngredients():
				if Util.isItemDescriptor(ingredient):
					if ingredient.classes == StuffedClasses.Undefined:
						Util.eprint(getName(), "classes are undefined due to ingredient ", ingredient.getName())
					
					
					recipeClasses &= ingredient.classes
			classes |= recipeClasses
			
	if classes == StuffedClasses.Undefined:
		classes = StuffedClasses.None

func addAppropriatingItem(item):
	if classes == StuffedClasses.Neutral: return
	
	
	appropriatingItems.push_back(item)
	


func calcAppropriation():
	if classes == StuffedClasses.Neutral: return
	
	for recipe in originatingRecipes:
		for ingredient in recipe.getAllIngredients():
			if not recipe.isTypeIngredient(ingredient):
				for item in ingredient.appropriatingItems:
					if not item in appropriatingItems:
						appropriatingItems.push_back(item)
						
	
	if gateItem != null:
		appropriatingItems.push_back(gateItem)

func getCraftingDepth() -> int:
	if originatingRecipes.empty(): return 0
	
	var depth: int
	for recipe in originatingRecipes:
		for ingredient in recipe.getAllIngredients():
			if not recipe.isTypeIngredient(ingredient):
				depth = max(depth, ingredient.getCraftingDepth())

	return depth + 1

func getPrice():
	return price

func getSellPrice():
	return ceil(getPrice() * 0.5)

func getSalePrice():
	return ceil(getPrice() * 0.5)

func canCraft(classId) -> bool:
	for recipe in originatingRecipes:
		var craftable = true
		for ingredient in recipe.getAllIngredients():
			if (Util.isItemDescriptor(ingredient) and 
				not ingredient.isAvailableFor(classId) and 
				not ItemBook.isItemInInventory(ingredient)):
					craftable = false
		if craftable:
			return true
	return false

func isCraftedItem() -> bool:
	return not originatingRecipes.empty()

func isGatedItem() -> bool:
	return gateItem != null

func isTreasure() -> bool:
	return randomUniquePool

func canOnlyExistOnce() -> bool:
	return tags & Item.Tag.Singular

func isTransient() -> bool:
	return tags & Item.Tag.Transient

func getWeight() -> float:
	return weight

func getThreshold() -> int:
	return threshold

func getThresholdWeight(itemCounter: Dictionary) -> float:
	var thresholdFactor = 1.0
	var numOwned = itemCounter.get(self, 0)
	if numOwned >= getThreshold() + 3:
		thresholdFactor = 0.02
	elif numOwned >= getThreshold() + 2:
		thresholdFactor = 0.1
	elif numOwned >= getThreshold() + 1:
		thresholdFactor = 0.2
	elif numOwned >= getThreshold():
		thresholdFactor = 0.4
	else:
		thresholdFactor = 1.0
	return thresholdFactor

func isShopItem() -> bool:
	return shopItem or ( not isCraftedItem() and not isGatedItem())

func hasType(type) -> bool:
	return type in types

func getTypes() -> Array:
	return types

func hasTag(tag) -> bool:
	return tag & tags

func isBag() -> bool:
	return Item.Type.Bag in types

func isWeapon() -> bool:
	return Item.Type.Weapon in types

func isMeleeWeapon() -> bool:
	return Item.Type.Melee in types and isWeapon()

func isRangedWeapon() -> bool:
	return Item.Type.Ranged in types and isWeapon()


func isStartingWeapon() -> bool:
	return isWeapon() and not identifier == "Stone"

func isGem() -> bool:
	return Item.Type.Gem in types

func isSubclassItem() -> bool:
	return startsSubclass != ""

func getFlavorTextSimple() -> String:
	return tr(str(descriptionKey, "_FLAVOR"))
	

func getFlavorText() -> String:
	var texts = []
	for suffix in ["", "2", "3"]:
		var flavor = Util.tra_nbs(str(descriptionKey, "_FLAVOR", suffix))
		if flavor != "" and flavor != ".":
			texts.push_back(flavor)
	
	
	
	if texts.empty():
		return ""
	else:
		return Util.pickRandomElement(texts)


func getNumRecipes() -> int:
	return recipes.size() + recipesAsIngredient.size()

func isReleased() -> bool:
	if releaseState == ReleaseState.Demo:
		return true
	elif releaseState == ReleaseState.Full:
		return Game.loadExclusiveContent()
	else:
		return Game.loadUnreleasedContent()

func getClassesAsArray() -> Array:
	var classArr = []
	var counter = 1
	for i in Game.getNumClasses():
		if classes & counter:
			classArr.push_back(counter)
		counter = counter << 1
	return classArr
