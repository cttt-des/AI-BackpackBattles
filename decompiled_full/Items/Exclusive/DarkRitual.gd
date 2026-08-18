extends Item

onready var crystalDescriptor = ItemBook.getDescriptor("Corrupted Crystal")
onready var debuffs: = int(getP("debuffs"))
onready var vampirism: = int(getP("vampirism"))
onready var darkSpeed: = getP("speed") / 100.0
var boosted: = 0

func canAffect(item):
	return item.hasType(Type.Dark)

func getData():
	return boosted

func setData(data):
	if data != null:
		boosted = data

func onBought():
	boosted = 1

func doCooldownEffect():
	inflictRandomDebuffs(debuffs)
	giveVampirism(vampirism)
	onAfterEffectFinished()

func onPrepare():
	var numDark = getNumAffectedItems()
	if numDark > 0:
		addSpeed(darkSpeed * numDark)

func onItemRoll(descr):
	if descr == crystalDescriptor and boosted > 0:
		ItemBook.multiplyWeight(1.5)

func onItemRolled(descr):
	if descr == crystalDescriptor:
		boosted -= 1
