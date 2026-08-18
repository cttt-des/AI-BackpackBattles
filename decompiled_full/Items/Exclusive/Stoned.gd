extends Item

onready var stoneDescriptor = ItemBook.getDescriptor("Stone")
onready var stoneGolemDescriptor = ItemBook.getDescriptor("Stone Golem")
onready var stoneArmorDescriptor = ItemBook.getDescriptor("Stone Armor")
onready var blockFactor: = getP("blockfordam") / 100.0
onready var damReduction: = getP("damreduction")

var protectionActive: bool
var boostedStones: = 0
var damReductionGiven = 0.0

func getData():
	return boostedStones

func setData(data):
	if data != null:
		boostedStones = data

func onBought():
	boostedStones = 4

func canBlock() -> bool:
	return true

func canAffect_global(item):
	return item.hasTag(Tag.Stone) or item.isA(stoneGolemDescriptor)

func onPrepare():
	
	connectForCombat(character(), "character_block_changed", "onBlockChanged")
	connectForCombat(character(), "character_damaged", "onDamaged")
	protectionActive = false
	damReductionGiven = 0.0
	
	for item in inventory.getItems():
		if canAffect_global(item):
			connectForCombat(item, "attacked", "onStoneAttacked")

func onStoneAttacked(damageRes):
	if damageRes.hasHit():
		giveBlock(ceil(damageRes.damage * blockFactor), true, damageRes.event)
		miniActivate()

func onDamaged(_healthChange, _event):
	checkBlock()

func onBlockChanged(_amount, _event):
	checkBlock()

func checkBlock():
	if protectionActive:
		if character().getBlock() == 0:
			protectionActive = false
			
			character().changeDamageResistance( - damReduction)
			damReductionGiven -= damReduction
	else:
		if character().getBlock() > 0:
			protectionActive = true
			
			character().changeDamageResistance(damReduction)
			damReductionGiven += damReduction





func onItemRoll(descr):
	if descr == stoneDescriptor and boostedStones > 0:
		ItemBook.multiplyWeight(1.7)

func onItemRolled(descr):
	if descr == stoneDescriptor:
		boostedStones -= 1
