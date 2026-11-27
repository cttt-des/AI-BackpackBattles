extends Food
var manaNeeded
var debuffs
var regen
var luck

func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Holy)


func onPrepare():
	character().changeBuffProtectionChance(getChance() + 
		getChance2() * getNumAffectedItems(CoreConst.Affected.Secondary))


func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		cleanseRandomDebuffs(debuffs, event)
		if character().getDebuffStacks() == 0:
			giveRegeneration(regen)
			giveLucky(luck)
	activate()

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	debuffs = int(getP("debuffs"))
	regen = int(getP("regen"))
	luck = int(getP("luck"))
