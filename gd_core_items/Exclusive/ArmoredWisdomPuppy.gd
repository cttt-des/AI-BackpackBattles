extends "res://gd_core_items/Exclusive/WisdomPuppy.gd"
var bonusBlock = 0
var cold: int

func onPrepare():
	.onPrepare()
	bonusBlock = 0


func doCooldownEffect():
	giveBlock(getBlock() + bonusBlock)
	cleanseCold(cold)
	activate()
	bonusBlock += getP3()

func _readyInit():
	._readyInit()
	cold = getP1()
