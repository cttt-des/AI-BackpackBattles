extends Weapon

onready var reflectStacks: = int(getP("reflect"))
onready var blockFactor = getP("blockfactor") / 100.0
onready var dam: = getP("dam")

func canAffect(item):
	return item.canBeEmpowered() or item.canBlock()

func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Block, blockFactor)

func onPreCombatStart():
	giveReflectStacks(reflectStacks)

func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(dam)
	activate(null, false)
