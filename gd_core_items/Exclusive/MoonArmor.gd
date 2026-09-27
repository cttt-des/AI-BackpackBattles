extends Item
var mana: int
var reflect: int

func canAffect(item):
	return item.hasType(CoreConst.Type.Magic)


func onCombatStart():
	giveBlock(getBlock() + getP1() * getNumAffectedItems())
	activate()


func doCooldownEffect():
	giveMana(mana)
	giveReflectStacks(reflect)
	activate()

func _readyInit():
	._readyInit()
	mana = getP("mana")
	reflect = getP("reflect")
