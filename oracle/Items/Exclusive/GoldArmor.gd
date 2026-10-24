extends Item

onready var gold: = int(getP("gold"))
onready var regen: = int(getP("regen"))
onready var cleanse: = int(getP("cleanse"))
onready var block: = getP("block")
onready var speedMalus: = getP("speed") / 100.0

func onShopEntered():
	giveGold(gold)

func canAffect(item):
	return item.hasType(Type.Holy)

func onPrepare():
	for item in inventory.getItems():
		if item.hasType(Type.Weapon):
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
