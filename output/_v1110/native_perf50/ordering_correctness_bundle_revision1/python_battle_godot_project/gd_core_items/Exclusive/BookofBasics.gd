extends Item
var bonusHealthFactor: int
var salesChance
var manaNeeded

func canAffect(item):
	return item.hasType(CoreConst.Type.Spell)


func onPrepare():
	bonusHealthFactor = 0
	for item in getAffectedItems():
		if item.isCrafted():
			bonusHealthFactor += 2
		else:
			bonusHealthFactor += 1


func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveMaxHealth(getP_m("maxhealth") + getP_m("maxhealth_spell") * bonusHealthFactor, 
		event)
	activate()


func onSaleRoll(item):
	pass

func _readyInit():
	._readyInit()
	salesChance = getShopChance() / 100.0
	manaNeeded = int(getP("manat"))
