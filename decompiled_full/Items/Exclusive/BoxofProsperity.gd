extends Bag

onready var activeParticles = $Icon / ActiveParticles
onready var activationParticles = $Icon / ActivationParticles
onready var requiredItems = getP("insideitems")

func canApplyEffect(toItem):
	return toItem.getRarity() >= Rarity.Godly

func onShopEntered():
	if conditionFulfilled():
		var gem = ItemBook.generateItem(ItemBook.getGemOfRarity(Rarity.Common))
		get_parent().add_child(gem)
		gem.global_position = global_position
		gem.pushToStorage(Game.STORAGEBOX.center + Util.randInBox(100, 100))
		gem.createGemParticles()
		activate()
		Game.saveRunState()

func onAffectedItemInsideAdded(_item):
	if getNumAffectedInside() == requiredItems:
		activationParticles.activate()
		activeParticles.activate()


func onItemRemoved(item):
	.onItemRemoved(item)
	if not conditionFulfilled():
		activeParticles.deactivate()

func conditionFulfilled() -> bool:
	return getNumAffectedInside() >= requiredItems




func onRemoveFromInventory():
	activeParticles.deactivate()

func onAddToInventory():
	if conditionFulfilled():
		activeParticles.activate()

func discard(withGems = true):
	activationParticles.instantClear()
	activeParticles.instantClear()
	.discard(withGems)
	
