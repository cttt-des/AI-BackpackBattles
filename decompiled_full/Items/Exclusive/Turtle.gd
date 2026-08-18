extends "res://Items/LeatherHelm.gd"

onready var extraDamBlock: = getP("bonus_damblock") / 100.0
onready var maxHealthBlock: = getP("block2") / 100.0

func canAffect(item):
	return item.hasType(Type.Shield)

func onPrepare():
	for item in getAffectedItems():
		item.modifyParam("damblock", extraDamBlock)

func onPreCombatStart():
	.onPreCombatStart()
	opponent().changeDamageResistance(damReduction)

func buffEnded():
	.buffEnded()
	opponent().changeDamageResistance( - damReduction)

func doCooldownEffect():
	var blockAmount = getBlock() + character().getMaxHealth() * maxHealthBlock
	giveBlock(blockAmount)
	activate()
