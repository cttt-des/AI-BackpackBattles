extends Item
const amuletColor = Color(0.34902, 0.415686, 0.45098)
var blockAcc: int
var blockForEmpower
var empowerForBlock

func canAffect(item):
	return item.canBlock()


func onPrepare():
	blockAcc = 0
	for item in getAffectedItems():
		connectForCombat(item, "gave_block", "onItemGaveBlock")


func onCombatStart():
	giveBlock()
	activate()


func onItemGaveBlock(amount, event):
	blockAcc += amount
	var empower = blockAcc / blockForEmpower
	blockAcc %= blockForEmpower
	if empower > 0:
		giveEmpower(empower * empowerForBlock, event)
		activate()

func _readyInit():
	._readyInit()
	blockForEmpower = int(getP("blockt"))
	empowerForBlock = int(getP("empower"))
	pass

