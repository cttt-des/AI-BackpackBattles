extends Bag

func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	.addToInventory(_inventory, _occupiedCells, _placedByPlayer)
	if ownerType == CoreConst.Owner.PlayerInventory:
		character().changeBaseMaxStamina()


func onRemoveFromInventory():
	.onRemoveFromInventory()
	if ownerType != CoreConst.Owner.BuildViewer:
		character().changeBaseMaxStamina()


func onPrepare():
	if isTypeInInventory(ctx.item_book.getDescriptor("Bagtacular")):
		var stamina = ctx.item_book.getDescriptor("Bagtacular").getP("stamina") / 100.0
		character().giveStaminaRegeneration(stamina)

func _readyInit():
	._readyInit()
	pass
