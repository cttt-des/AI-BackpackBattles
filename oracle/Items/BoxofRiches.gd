extends Item

var numGems = 1

const gemOdds = [
	16, 
	8, 
	2, 
	1, 
	0.5
]

func onShopEntered():
	for i in numGems:
		var gem = ItemBook.generateItem(ItemBook.getGemOfRarity(Rarity.Common))
		
		var adjacentCells = inventory.getAdjacentCells(occupiedCells)
		placeGeneratedItem(gem, adjacentCells)
		
		gem.createGemParticles()
	
	activate(null, false)
	Game.saveRunState()

func getGatedDescriptor(rarityOdds, numHighRolls = 0) -> ItemDescriptor:
	var rarity = 0
	if Util.rng.randf() < 0.25:
		
		rarity = ItemBook.getRandomRarity(rarityOdds)
	else:
		
		var maxRarity = Item.Rarity.Common - 1
		for r in rarityOdds:
			if r > 0:
				maxRarity += 1
		rarity = min(maxRarity, ItemBook.getRandomRarity(gemOdds))
		
	
	rarity += numHighRolls
	rarity = min(rarity, Item.Rarity.Godly)
	
	return ItemBook.getGemOfRarity(rarity)

func getRelatedItemHeight() -> int:
	return 50


func onGateItemRoll():
	if rollShopChance():
		for item in Game.shopSceneNode.gateItemCandidates:
			if item.isA(descriptor): return
		Game.shopSceneNode.addGateItem(self)
