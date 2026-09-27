extends Item
var protectionActive: bool
var boostedStones: = 0
var damReductionGiven = 0.0
var stoneDescriptor
var stoneGolemDescriptor
var stoneArmorDescriptor
var blockFactor
var damReduction

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
	return item.hasTag(CoreConst.Tag.Stone) or item.isA(stoneGolemDescriptor)


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
	pass

func onItemRolled(descr):
	if descr == stoneDescriptor:
		boostedStones -= 1

func _readyInit():
	._readyInit()
	stoneDescriptor = ctx.item_book.getDescriptor("Stone")
	stoneGolemDescriptor = ctx.item_book.getDescriptor("Stone Golem")
	stoneArmorDescriptor = ctx.item_book.getDescriptor("Stone Armor")
	blockFactor = getP("blockfordam") / 100.0
	damReduction = getP("damreduction")
