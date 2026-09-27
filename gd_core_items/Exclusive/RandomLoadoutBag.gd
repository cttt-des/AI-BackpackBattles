extends Bag
var mainBags = {
	CoreConst.Classes.Ranger: ["Ranger Bag", "Vineweave Basket"], 
	CoreConst.Classes.Reaper: ["Storage Coffin", "Relic Case"], 
	CoreConst.Classes.Pyromancer: ["Fire Pit", "Portable Altar"], 
	CoreConst.Classes.Berserker: ["Berserker Bag", "Toolbox"], 
	CoreConst.Classes_Full.Mage: ["Scholar Bag", "Puzzlebox"], 
	CoreConst.Classes_Full.Adventurer: ["Bag of Giving", "Sewing Case"], 
	CoreConst.Classes_Full.Engineer: ["Engineer Box", "Engineer Bag 2"]
}
var compensationValue = {
	CoreConst.Classes.Ranger: [0, 0], 
	CoreConst.Classes.Reaper: [1, 0], 
	CoreConst.Classes.Pyromancer: [2, 1], 
	CoreConst.Classes.Berserker: [1, 0], 
	CoreConst.Classes_Full.Mage: [0, 0], 
	CoreConst.Classes_Full.Adventurer: [0, 0], 
	CoreConst.Classes_Full.Engineer: [0, 0]
}
const bagRarityWeights = {
	CoreConst.Rarity.Common: 2, 
	CoreConst.Rarity.Rare: 0.5, 
	CoreConst.Rarity.Epic: 0.2, 
	CoreConst.Rarity.Legendary: 0.1, 
	CoreConst.Rarity.Godly: 0.05, 
}
var excludeNames = [
	"Acorn Collar", 
	"Unstable Recombobulator", 
	"Draconic Orb", 
	"Stone Skin Potion", 
	"Divine Potion"
]
var bagCells: Array

func addBagWherePossible(bag, startPos: Vector2):
	pass

func addItemWherePossible(item):
	pass

func shopOpened():
	pass

func prepareParticles():
	if ownerType == CoreConst.Owner.PlayerInventory:
		ctx.util.callDelayed(self, "createRevealParticles", 0.4)


func createRevealParticles():
	pass

func _readyInit():
	._readyInit()
	pass

