extends Item
const gatedItems = ["Emerald Egg", "Amethyst Egg", "Sapphire Egg"]

func canAffect(item):
	return item is DragonEgg or item.hasTag(CoreConst.Tag.Dragon)


func onPrepare():
	for item in getAffectedItems():
		if item.hasTag(CoreConst.Tag.Dragon):
			connectForCombat(item, "attacked", "onDragonAttacked")
			


func onDragonAttacked(damageRes):
	heal(getP_m("heal"), damageRes.event)
	miniActivate()


func onCombatStart():
	giveLucky(getP2())
	giveRegeneration(getP3())
	giveMana(getP4())
	giveHeat(getP5())
	activate()


func getGatedDescriptor(rarity) -> CoreItemData:
	return ctx.item_book.getDescriptor(ctx.util.pickRandomElement(gatedItems))

func _readyInit():
	._readyInit()
	pass
