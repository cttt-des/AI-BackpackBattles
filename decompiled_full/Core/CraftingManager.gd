extends Node

signal recipes_updated

const craftingPreviewBondScene = preload("res://Items/CraftingPreviewBond.tscn")

var itemsAvailablePending = []
var itemsRemovedPending = []
var updatePending = false
var fusionPreviews = []

func itemAdded(item):
	if item.isShowCaseItem(): return
	
	itemsAvailablePending.push_back(item)
	if not updatePending:
		updatePending = true
		call_deferred("updateRecipes")
	
func itemRemoved(item):
	if item.isShowCaseItem(): return
	
	itemsRemovedPending.push_back(item)
	if not updatePending:
		updatePending = true
		call_deferred("updateRecipes")

func itemShifted(item):
	
	itemRemoved(item)
	itemAdded(item)

func updateRecipes():
	updatePending = false
	
	for removedItem in itemsRemovedPending:
		
		if removedItem.isBaseItem():
			
			for bondedItem in removedItem.bondedIngredients:
				
				bondedItem.removeBondedBaseItem()
				if not bondedItem in itemsRemovedPending:
					itemsAvailablePending.push_back(bondedItem)
				
			removedItem.removeAllIngredients()
		else:
			
			if removedItem.bondedBaseItem:
				
				removedItem.bondedBaseItem.removeBondedIngredient(removedItem)
				if not removedItem.bondedBaseItem in itemsRemovedPending:
					itemsAvailablePending.push_back(removedItem.bondedBaseItem)
				removedItem.removeBondedBaseItem()
				


	
	
	
	var cleanedAvailable = []
	for addedItem in itemsAvailablePending:
		



		if addedItem.placed or (addedItem.isGem() and addedItem.socket != null):
			cleanedAvailable.push_back(addedItem)
	
	
	for addedItem in cleanedAvailable:
		
		if not addedItem.isAvailableForCrafting():
			
			continue
		
		var neighbors = addedItem.getCraftableNeighbors()
		
		if addedItem.curRecipe:
			if not addedItem.isRecipeFinished():
				for neighbor in neighbors:
					if addedItem.curRecipe.checkNeighbor(addedItem.bondedIngredients, neighbor):
						addIngredient(addedItem, addedItem.curRecipe, neighbor)
			continue
		
		
		var bestScore = 0.0
		var bestRecipe = null
		var bestIngredients = []
		var bestBaseItem = null
		
		
		for neighbor in neighbors:
			if not neighbor.isBoundAsIngredient():
				var score = neighbor.considerAsBond(addedItem)
				if score:
					if score[1] > bestScore:
						bestScore = score[1]
						bestRecipe = score[0]
						bestBaseItem = neighbor
			
		if bestRecipe:
			
			addIngredient(bestBaseItem, bestRecipe, addedItem)
			
			
		else:
			
			for recipe in addedItem.getRecipes():
				
				var bonds = []
				for neighbor in neighbors:
					if recipe.getProgress(bonds) < 1:
						
						if recipe.checkNeighbor(bonds, neighbor):
							bonds.push_back(neighbor)
				
				var progress = float(bonds.size()) / recipe.getNumIngredients()
				
				if recipe.isCatalystRecipe():
					progress += 0.01
				
				if recipe.hasBagIngredient():
					progress -= 0.02
				
				if progress > bestScore:
					bestIngredients = bonds
					bestScore = progress
					bestRecipe = recipe
			
			if bestRecipe:
				for ingredient in bestIngredients:
					addIngredient(addedItem, bestRecipe, ingredient)
					
				
	
	emit_signal("recipes_updated")
	
	
	
	if cleanedAvailable.size() == 1:
		var item = cleanedAvailable[0]
		if item.curRecipe == null and not item.isBoundAsIngredient():
			var potentialFusePartners = {}
			var fuseTypes = []
			
			for recipe in item.descriptor.recipes:
				for ingredient in recipe.ingredients:
					if recipe.isTypeIngredient(ingredient):
						fuseTypes.push_back(ingredient)
					else:
						potentialFusePartners[ingredient] = true
			
			for recipe in item.descriptor.recipesAsIngredient:
				potentialFusePartners[recipe.baseItem] = true
			
			for neighbor in item.getBusyNeighbors():
				
				var isPotentialFusePartner = neighbor.descriptor in potentialFusePartners
				if not isPotentialFusePartner:
					
					for type in fuseTypes:
						if neighbor.hasType(type):
							isPotentialFusePartner = true
				
				if isPotentialFusePartner:
					var baseItem
					if neighbor.isBoundAsIngredient():
						baseItem = neighbor.bondedBaseItem
					else:
						baseItem = neighbor
					
					for bond in baseItem.bondVisuals:
						if bond.endNode == neighbor or bond.startNode == neighbor:
							bond.flash()
					
					neighbor.playBondFailedAnimation()
	
	itemsAvailablePending.clear()
	itemsRemovedPending.clear()
	

func addIngredient(baseItem, recipe, ingredient):
	baseItem.addBondedIngredient(recipe, ingredient)
	ingredient.addToBaseItem(baseItem)

func previewFusionToItem(baseItem):
	for item in ItemBook.getInventoryStorageShopItems():
		if item != baseItem:
			item.previewFusionToItem(baseItem)

func createFusionPreview(item1, item2, focusItem):
	
	if not Game.hasHoverFocus(focusItem) and not Game.draggedItem == focusItem:
		
		
		return
	
	
	var visual1 = ObjectPool.instance(craftingPreviewBondScene)
	item1.get_parent().add_child(visual1)
	visual1.create(item1, item2, false)
	fusionPreviews.push_back(visual1)
	
	var visual2 = ObjectPool.instance(craftingPreviewBondScene)
	item2.get_parent().add_child(visual2)
	visual2.create(item2, item1, true)
	fusionPreviews.push_back(visual2)

func hideFusionPreviews(stopOrientation = false):
	
	
	for preview in fusionPreviews:
		
		preview.breakBond()
		if stopOrientation:
			preview.stopOrientation()
	fusionPreviews.clear()
