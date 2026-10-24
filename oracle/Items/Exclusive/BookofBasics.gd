extends Item

onready var salesChance: = getShopChance() / 100.0
onready var manaNeeded: = int(getP("manat"))
var bonusHealthFactor: int

func canAffect(item):
	return item.hasType(Type.Spell)

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
	if item != null and (item.hasType(Type.Book) or item.hasType(Type.Spell)):
		Game.shopSceneNode.addBonusSalesChance(salesChance)
