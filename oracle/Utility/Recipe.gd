extends Reference
class_name Recipe

var baseItem: ItemDescriptor
var ingredients = []
var catalyst = []
var fusedItem: ItemDescriptor
var allIngredients = []

func fromString(baseItem_, string):
	var formula = string.split(">")
	var ingredientNames = formula[0].split("+")
	
	var catalyst_ = []
	for i in ingredientNames.size():
		var name = ingredientNames[i]
		if name.ends_with("*"):
			catalyst_.push_back(true)
			ingredientNames[i] = name.trim_suffix("*")
		else:
			catalyst_.push_back(false)
	
	return init(baseItem_, ingredientNames, catalyst_, formula[1])
	
func init(baseItem_, ingredients_: Array, catalyst_: Array, fusedItem_):
	if baseItem_ is ItemDescriptor:
		baseItem = baseItem_
	else:
		baseItem = ItemBook.getDescriptor(baseItem_)
	
	for ingredient in ingredients_:
		if ingredient in Item.Type:
			ingredients.push_back(Item.Type[ingredient])
		elif ingredient is ItemDescriptor:
			ingredients.push_back(ingredient)
			if not ingredient.isReleased():
				return
		else:
			var descriptor = ItemBook.getDescriptor(ingredient)
			ingredients.push_back(descriptor)
			if not descriptor.isReleased():
				return
	
	catalyst = catalyst_
	if fusedItem_ is ItemDescriptor:
		fusedItem = fusedItem_
	else:
		fusedItem = ItemBook.getDescriptor(fusedItem_)
	
	if not fusedItem.isReleased():
		return
	
	allIngredients.push_back(baseItem)
	allIngredients.append_array(ingredients)
	
	
	baseItem.recipes.push_back(self)
	fusedItem.originatingRecipes.push_back(self)
	for ingredient in ingredients:
		if not isTypeIngredient(ingredient):
			ingredient.recipesAsIngredient.push_back(self)
	







	
	return self

func isAvailable(item):
	return fusedItem.canCraft(item.character().characterClass)

func isBaseItem(item) -> bool:
	return item.descriptor == baseItem

func fitsIngredient(item, ingredient):
	if isTypeIngredient(ingredient):
		return item.hasType(ingredient)
	else:
		return item.getRecipeDescriptor() == ingredient

func hasBagIngredient() -> bool:
	for ingredient in ingredients:
		if not isTypeIngredient(ingredient):
			if ingredient.isBag():
				return true
	return false

func findBonds(neighbors) -> Array:
	var bonds = []
	for ingredient in ingredients:
		for neighbor in neighbors:
			if (fitsIngredient(neighbor, ingredient) and 
				not neighbor.isBoundAsIngredient() and 
				not neighbor.isLocked()):
				bonds.push_back(neighbor)
				neighbors.erase(neighbor)
				break
		
		
		
	return bonds

func getNumIngredients():
	return ingredients.size()


func getProgress(curBonds):
	return curBonds.size() / float(ingredients.size())


func getMissingIngredients(curBonds) -> Array:
	var missing = []
	var counter = getIngredientCounter(false)
	for bond in curBonds:
		Util.dictSub(counter, bond.descriptor)
	
	for descriptor in counter:
		for num in counter[descriptor]:
			missing.push_back(descriptor)
	return missing


func getCurIngredientsCounter(curBonds) -> Array:
	var current = {}
	var maxCounter = getIngredientCounter(false)
	for bond in curBonds:
		Util.dictAdd(current, bond.descriptor)
	
	var currentCounter: = []
	for descriptor in maxCounter:
		
		var cur = current.get(descriptor, 0)
		if cur < maxCounter[descriptor]:
			currentCounter.push_back([descriptor, 
				cur, maxCounter[descriptor]])
	
	return currentCounter

func checkNeighbor(curBonds, neighbor) -> bool:
	if not neighbor.canStartNewRecipe(): return false
	
	if not neighbor.isPlaced(): return false
	
	var curBondDescriptors = []
	for item in curBonds:
		curBondDescriptors.push_back(item.descriptor)
	
	
	var missingIngredients = Util.subtractArr(ingredients, curBondDescriptors)
	
	for ingredient in missingIngredients:
		if fitsIngredient(neighbor, ingredient):
			return true
	
	return false


func isCatalystRecipe() -> bool:
	return catalyst[0]


func isTypeIngredient(ingredient) -> bool:
	return typeof(ingredient) == TYPE_INT

func isNeighborCatalyst(neighbor) -> bool:
	for i in ingredients.size():
		if fitsIngredient(neighbor, ingredients[i]):
			return catalyst[i]
	
	Util.eassert(false)
	return false

func isDescriptorCatalyst(descriptor: ItemDescriptor) -> bool:
	for i in ingredients.size():
		if not isTypeIngredient(ingredients[i]):
			if descriptor == ingredients[i]:
				return catalyst[i]
	return false


func fuse(bItem, curBonds):
	
	for item in curBonds:
		if isNeighborCatalyst(item):
			item.catalystFusingFinished()
			if item.isGem() and item.getItem() == bItem:
				item.pushToStorage(Game.STORAGEBOX.center)
		else:
			if item.isGem() and item.socket:
				var socket = item.socket
				socket.onPickupGem()
				socket.hideSocket()
				item.ownerType = Item.Owner.PlayerStorageBox
			elif item.placed:
				item.inventory.removeItem(item)
			
			item.discard(false)
		
	
	if fusedItem.isBag():
		bItem.pushGemsToStorage()
		bItem.inventory.removeItem(bItem)
		bItem.discard(false)
		var newItem = ItemBook.instantiateItem(fusedItem)
		newItem.wasJustCrafted = true
		Game.playerNode.add_child(newItem)
		newItem.global_position = bItem.global_position
		newItem.pushToStorage(Game.STORAGEBOX.center + Util.randInBox(100, 100))
		Game.onItemCrafted(fusedItem)
		newItem.onCraftedFrom(bItem, curBonds)
		
	elif bItem.isGem() and bItem.socket:
		
		var newItem = ItemBook.instantiateItem(fusedItem)
		newItem.wasJustCrafted = true
		var socket = bItem.socket
		socket.onPickupGem()
		socket.add_child(newItem)
		newItem.global_position = bItem.global_position
		newItem.addToSocket(socket)
		CraftingManager.itemRemoved(bItem)
		bItem.ownerType = Item.Owner.PlayerStorageBox
		bItem.discard(false)
		Game.onItemCrafted(fusedItem)
		newItem.onCraftedFrom(bItem, curBonds)
		
	else:
		if bItem.allowGeneratingFusionItem():
			
			var newItem = ItemBook.instantiateItem(fusedItem)
			newItem.wasJustCrafted = true
			
			var craftingCenter = bItem.global_position
			var wasAddedToInventory = bItem.inventory.replaceItem(bItem, newItem)
			if wasAddedToInventory:
				newItem.playCraftedAnimation(craftingCenter)
			
			
			
			var numSockets = newItem.getNumSockets()
			var socketI = 0
			var gems = bItem.getGemsNoNull()
			for item in curBonds:
				if not isNeighborCatalyst(item):
					gems.append_array(item.getGemsNoNull())
			
			if numSockets > 0 and gems.size() > 0:
				while true:
					if socketI < gems.size() and socketI < numSockets:
						var gem = gems[socketI]
						if not gem.fusing:
							gem.unsocket()
							gem.get_parent().remove_child(gem)
							newItem.setGem(socketI, gem)
						socketI += 1
					else:
						break
				
			for i in range(socketI, gems.size()):
				var gem = gems[i]
				if not gem.fusing:
					gem.pushToStorage(Game.STORAGEBOX.center)
			
			Game.onItemCrafted(fusedItem)
			newItem.onCraftedFrom(bItem, curBonds)
			
		else:
			
			for item in curBonds:
				if not isNeighborCatalyst(item):
					item.pushGemsToStorage()
			bItem.inventory.removeItem(bItem)
			bItem.pushGemsToStorage()
			bItem.discard(false)

func getCatalystBonds(curBonds):
	var nonCatalystBonds = []
	for neighbor in curBonds:
		if isNeighborCatalyst(neighbor):
			nonCatalystBonds.push_back(neighbor)
	return nonCatalystBonds

func getNonCatalystBonds(curBonds):
	return Util.subtractArr(curBonds, getCatalystBonds(curBonds))

func getAllIngredients():
	return allIngredients


func isAvailableForClass(classI):
	if not baseItem.isAvailableFor(classI):
		return false
	
	for ingredient in ingredients:
		if not isTypeIngredient(ingredient):
			if not ingredient.isAvailableFor(classI):
				return false
	
	return true

func getIngredientCounter(withTypes = true) -> Dictionary:
	var counter = {}
	for descriptor in ingredients:
		if withTypes or not isTypeIngredient(descriptor):
			Util.dictAdd(counter, descriptor)
	return counter
