extends Item
var unhealing
var vampirism
var vampiricSpeed
var bloodAmulet

func canAffect(item):
	return item.hasType(CoreConst.Type.Vampiric)


func onPrepare():
	character().giveUnhealing(unhealing)
	addSpeed(vampiricSpeed * getNumAffectedItems())


func doCooldownEffect():
	giveVampirism(vampirism)
	activate()


func onItemRoll(descr):
	pass

func _readyInit():
	._readyInit()
	unhealing = getP("unhealing") / 100.0
	vampirism = int(getP("vampirism"))
	vampiricSpeed = getP("speed") / 100.0
	bloodAmulet = ctx.item_book.getDescriptor("Blood Amulet")
