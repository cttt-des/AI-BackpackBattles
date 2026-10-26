extends "res://gd_core_items/LeatherHelm.gd"
var extraDamBlock
var maxHealthBlock

func canAffect(item):
	return item.hasType(CoreConst.Type.Shield)


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

func _readyInit():
	._readyInit()
	extraDamBlock = getP("bonus_damblock") / 100.0
	maxHealthBlock = getP("block2") / 100.0
