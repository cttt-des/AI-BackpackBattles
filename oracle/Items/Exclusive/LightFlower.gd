extends Food

onready var manaNeeded: = int(getP("manat"))
onready var debuffs: = int(getP("debuffs"))
onready var regen: = int(getP("regen"))
onready var luck: = int(getP("luck"))

func canAffect_secondary(item):
	return item.hasType(Type.Holy)

func onPrepare():
	character().changeBuffProtectionChance(getChance() + 
		getChance2() * getNumAffectedItems(Affected.Secondary))

func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		cleanseRandomDebuffs(debuffs, event)
		if character().getDebuffStacks() == 0:
			giveRegeneration(regen)
			giveLucky(luck)
	activate()
