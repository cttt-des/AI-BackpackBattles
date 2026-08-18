extends Item

onready var buffFactor: = getP("buffs") / 100.0
onready var buffLimit: = int(getP("max"))

func canAffect(item):
	return item.hasType(Type.Holy)

func onPrepare():
	var totalChance = getChance() + getNumAffectedItems() * getChance2()
	character().changeAllDebuffsReflectChance(totalChance)

func doCooldownEffect():
	multiplyBuffsLimit(buffFactor, buffLimit)
	onAfterEffectFinished()

