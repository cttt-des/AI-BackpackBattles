extends Item
var boosted: = 0
var mana
var magicSpeed
var bonusBuffs
var manaOrbDescriptor

func getData():
	return boosted


func setData(data):
	if data != null:
		boosted = data


func onBought():
	boosted = 1


func canAffect(item):
	return item.hasType(CoreConst.Type.Magic)


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
	pass

func onItemRolled(descr):
	if descr == manaOrbDescriptor:
		boosted -= 1

func _readyInit():
	._readyInit()
	mana = int(getP("mana"))
	magicSpeed = getP("speed") / 100.0
	bonusBuffs = int(getP("buffs"))
	manaOrbDescriptor = ctx.item_book.getDescriptor("Mana Orb")
