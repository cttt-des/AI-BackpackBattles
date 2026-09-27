extends Item
var regen
var mana
var chainPosition

func onPrepare():
	for item in inventory.getItems():
		if item.hasType(CoreConst.Type.Card):
			connectForCombat(item, "activated", "onCardRevealed")


func onCardRevealed(event):
	var card = event.getOrigin()
	giveRegeneration(regen, event)
	if card.chainPosition + 1 >= chainPosition:
		giveMana(mana, event)
	activate()

func _readyInit():
	._readyInit()
	regen = int(getP("regen"))
	mana = int(getP("mana"))
	chainPosition = int(getP("pos"))
