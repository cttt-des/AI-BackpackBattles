extends "res://Items/Exclusive/WisdomPuppy.gd"

onready var cold: int = getP1()

var bonusBlock = 0

func onPrepare():
	.onPrepare()
	bonusBlock = 0

func doCooldownEffect():
	giveBlock(getBlock() + bonusBlock)
	cleanseCold(cold)
	activate()
	bonusBlock += getP3()
