extends Item

const gatedItems = ["Emerald Egg", "Amethyst Egg", "Sapphire Egg"]

func canAffect(item):
	return item is DragonEgg or item.hasTag(Tag.Dragon)

func onPrepare():
	for item in getAffectedItems():
		if item.hasTag(Tag.Dragon):
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

func getGatedDescriptor(rarity) -> ItemDescriptor:
	return ItemBook.getDescriptor(Util.pickRandomElement(gatedItems))
