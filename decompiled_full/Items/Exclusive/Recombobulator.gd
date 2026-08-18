extends Item

onready var idleAnimation = $Icon / AnimationPlayer

var unstableFilters = (ItemBook.Filter.Amulets + 
								ItemBook.Filter.Crafted + 
								ItemBook.Filter.Gems)

var stableFilters = (ItemBook.Filter.Crafted + 
						ItemBook.Filter.Gated + 
						ItemBook.Filter.OtherClasses + 
						ItemBook.Filter.AnyRarity)

var pool = ItemPool.new()

export var stable = true

func _ready():
	CraftingManager.connect("recipes_updated", self, "findBondsWithAffectedItems")

func canAffect(item):
	return not item.isBag() and (item.canStartNewRecipe() or item.bondedBaseItem == self)

func cacheAffectedItemsForCombat():
	.cacheAffectedItemsForCombat()
	var arr = getItemsInAffectedCells_cached()
	cachedAffectedItems[Affected.Primary] = arr



func readyToFuse() -> bool:
	if stable:
		return not bondedIngredients.empty()
	else:
		return bondedBaseItem == null

func onFusingFinished(validBonds):
	.onFusingFinished(validBonds)
	var value = int(getP("bonusvalue"))
	
	for item in validBonds:
		value += item.getPrice()
	
	if not stable:
		value += getPrice()
	
	var excluded: = {}
	for item in validBonds:
		excluded[item.descriptor] = true
	
	excluded[ItemBook.unstableRecombobulatorDescriptor] = true
	
	var filters = stableFilters if stable else unstableFilters
	
	pool.deleteAfterDraw = true
	pool.resetPool()
	
	for descr in ItemBook.items.values():
		if (ItemBook.canBeGenerated(descr, filters) and 
			not descr in excluded):
			
			pool.addItem(descr)
	
	pool.pool.shuffle()
	pool.sortItems()
	
	
	
	while value > 0:
		pool.setPrice(value)
		var item = pool.getRandomItemTopHeavy(0)
		value -= item.getPrice()
		
		ItemBook.generateAndStorageItem(item, global_position)
	
	if not stable:
		inventory.removeItem(self)
		discard()
	else:
		activate()
	
	Game.saveRunState()
	
	if validBonds.size() >= 8:
		SteamHelper.unlockAchievement("Recombobulator")

func reactToDropResult(dropResult):
	.reactToDropResult(dropResult)
	if wasAddedToInventory(dropResult):
		idleAnimation.stop()
		idleAnimation.play("Idle3")

func doCooldownEffect():
	giveRandomBuffs(1)
	cleanseRandomDebuffs(1)
	activate()

func getCounterValue() -> int:
	return getAffectedGoldValue()
