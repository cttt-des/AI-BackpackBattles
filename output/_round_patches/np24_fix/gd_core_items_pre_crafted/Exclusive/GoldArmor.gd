extends Item
var gold
var regen
var cleanse
var block
var speedMalus

func onShopEntered():
	giveGold(gold)


func canAffect(item):
	return item.hasType(CoreConst.Type.Holy)


func onPrepare():
	for item in inventory.getItems():
		if item.hasType(CoreConst.Type.Weapon):
			item.reduceSpeed(speedMalus)


func onCombatStart():
	giveRegeneration(getNumAffectedItems() * regen)
	giveBlock()
	activate()


func doCooldownEffect():
	cleanseRandomDebuffs(cleanse)
	if character().getDebuffStacks() == 0:
		giveBlock(block)
	
	activate()

func _readyInit():
	._readyInit()
	gold = int(getP("gold"))
	regen = int(getP("regen"))
	cleanse = int(getP("cleanse"))
	block = getP("block")
	speedMalus = getP("speed") / 100.0
