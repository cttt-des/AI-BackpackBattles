extends Item

onready var regen: = int(getP("regen"))
onready var mana: = int(getP("mana"))
onready var chainPosition: = int(getP("pos"))

func onPrepare():
	for item in inventory.getItems():
		if item.hasType(Type.Card):
			connectForCombat(item, "activated", "onCardRevealed")

func onCardRevealed(event):
	var card = event.getOrigin()
	giveRegeneration(regen, event)
	if card.chainPosition + 1 >= chainPosition:
		giveMana(mana, event)
	activate()
