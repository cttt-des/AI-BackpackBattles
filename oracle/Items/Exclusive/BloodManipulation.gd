extends Item

onready var unhealing: = getP("unhealing") / 100.0
onready var vampirism: = int(getP("vampirism"))
onready var vampiricSpeed: = getP("speed") / 100.0
onready var bloodAmulet = ItemBook.getDescriptor("Blood Amulet")

func canAffect(item):
	return item.hasType(Type.Vampiric)

func onPrepare():
	character().giveUnhealing(unhealing)
	addSpeed(vampiricSpeed * getNumAffectedItems())

func doCooldownEffect():
	giveVampirism(vampirism)
	activate()

func onItemRoll(descr):
	if descr.hasType(Type.Vampiric):
		if descr == bloodAmulet:
			ItemBook.multiplyWeight(1.5)
		else:
			ItemBook.multiplyWeight(1.3)
