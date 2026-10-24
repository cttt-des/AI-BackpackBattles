extends Bag

func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	.addToInventory(_inventory, _occupiedCells, _placedByPlayer)
	if ownerType == Owner.PlayerInventory:
		character().changeBaseMaxStamina()

func onRemoveFromInventory():
	.onRemoveFromInventory()
	if ownerType != Owner.BuildViewer:
		character().changeBaseMaxStamina()

func onPrepare():
	if isTypeInInventory(ItemBook.bagtacularDescriptor):
		var stamina = ItemBook.bagtacularDescriptor.getP("stamina") / 100.0
		character().giveStaminaRegeneration(stamina)
