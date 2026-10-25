extends Item
var blockAcc: int
var boostedGarlic: = 0
var garlicDescriptor
var garlicBlockBonus
var blockForPoison
var poisonForBlock

func canAffect(item):
	return item.isA(garlicDescriptor) or item.canBlock()


func onBought():
	boostedGarlic = 3


func getData():
	return boostedGarlic


func setData(data):
	if data != null:
		boostedGarlic = data


func onPrepare():
	blockAcc = 0
	
	for item in getAffectedItems():
		if item.isA(garlicDescriptor):
			item.addBonusBlock(garlicBlockBonus)
		if item.canBlock():
			connectForCombat(item, "gave_block", "onItemGaveBlock")


func onItemGaveBlock(amount, event):
	blockAcc += amount
	var poison = blockAcc / blockForPoison
	blockAcc %= blockForPoison
	if poison > 0:
		inflictPoison(poison * poisonForBlock, event)
		activate()


func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr == garlicDescriptor:
		boostedGarlic -= 1
	

func _readyInit():
	._readyInit()
	garlicDescriptor = ctx.item_book.getDescriptor("Garlic")
	garlicBlockBonus = int(getP("blockbonus"))
	blockForPoison = int(getP("blockt"))
	poisonForBlock = int(getP("poison"))
