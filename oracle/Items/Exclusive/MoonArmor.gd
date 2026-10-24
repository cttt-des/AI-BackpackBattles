extends Item

onready var mana: int = getP("mana")
onready var reflect: int = getP("reflect")

func canAffect(item):
	return item.hasType(Type.Magic)

func onCombatStart():
	giveBlock(getBlock() + getP1() * getNumAffectedItems())
	activate()

func doCooldownEffect():
	giveMana(mana)
	giveReflectStacks(reflect)
	activate()
