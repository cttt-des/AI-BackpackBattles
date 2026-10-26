extends Item
var speedPerAffected
var manaNeeded
var numDebuffs
var block2

func canAffect(item):
	return item.hasType(CoreConst.Type.Holy) or item.hasType(CoreConst.Type.Magic)


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

func _readyInit():
	._readyInit()
	speedPerAffected = getP("speed") / 100.0
	manaNeeded = int(getP("manat"))
	numDebuffs = int(getP("cleanse"))
	block2 = int(getP("block"))
