extends Item

onready var speedPerAffected: = getP("speed") / 100.0
onready var manaNeeded: = int(getP("manat"))
onready var numDebuffs: = int(getP("cleanse"))
onready var block2: = int(getP("block"))

func canAffect(item):
	return item.hasType(Type.Holy) or item.hasType(Type.Magic)

func onPrepare():
	addSpeed(getNumAffectedItems() * speedPerAffected)

func onCombatStart():
	giveBlock()
	activate()

func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		cleanseRandomDebuffs(numDebuffs, event)
		giveBlock(block2, true, event)
	activate()
