extends Item
var boosted: = 0
var crystalDescriptor
var debuffs
var vampirism
var darkSpeed

func canAffect(item):
	return item.hasType(CoreConst.Type.Dark)


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
	pass

func onItemRolled(descr):
	if descr == crystalDescriptor:
		boosted -= 1

func _readyInit():
	._readyInit()
	crystalDescriptor = ctx.item_book.getDescriptor("Corrupted Crystal")
	debuffs = int(getP("debuffs"))
	vampirism = int(getP("vampirism"))
	darkSpeed = getP("speed") / 100.0
