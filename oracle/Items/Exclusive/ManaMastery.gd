extends Item

onready var mana: = int(getP("mana"))
onready var magicSpeed: = getP("speed") / 100.0
onready var bonusBuffs: = int(getP("buffs"))
onready var manaOrbDescriptor = ItemBook.getDescriptor("Mana Orb")
var boosted: = 0

func getData():
	return boosted

func setData(data):
	if data != null:
		boosted = data

func onBought():
	boosted = 1

func canAffect(item):
	return item.hasType(Type.Magic)

func canAffect_global(item):
	return item.isA(manaOrbDescriptor)

func onPrepare():
	var numMagic: = getNumAffectedItems()
	if numMagic > 0:
		addSpeed(magicSpeed * numMagic)

func onPreCombatStart():
	for manaOrb in getAllInInventoryOfType(manaOrbDescriptor):
		manaOrb.addBonusRandomBuffs(bonusBuffs)

func doCooldownEffect():
	giveMana(mana)
	activate()

func onItemRoll(descr):
	if descr == manaOrbDescriptor and boosted > 0:
		ItemBook.multiplyWeight(1.8)

func onItemRolled(descr):
	if descr == manaOrbDescriptor:
		boosted -= 1
