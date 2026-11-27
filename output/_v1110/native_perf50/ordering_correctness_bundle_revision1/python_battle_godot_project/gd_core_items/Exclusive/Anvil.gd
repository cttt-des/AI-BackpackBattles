extends Item

func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	.addToInventory(_inventory, _occupiedCells, _placedByPlayer)


func onRemoveFromInventory():
	pass

func onCraft(_itemDescriptor):
	pass

func canAffect(item):
	return item.isCrafted()


func canAffect_secondary(item):
	return item.isWeapon()


func onPreCombatStart():
	var numCrafted = getAffectedItems().size()
	if numCrafted > 0:
		var bonusDamage = getP1() * numCrafted
		var staminaReduction = - getP2() * numCrafted
		for affectedWeapon in getAffectedItems(CoreConst.Affected.Secondary):
			if affectedWeapon.canBeEmpowered():
				affectedWeapon.addBonusDamage(bonusDamage)
				var event = ctx.combat_log.createEvent_DamageBuff(self, affectedWeapon, bonusDamage, character().playerId)
				ctx.bus.logEvent(event)
			
			affectedWeapon.changeStaminaFactor(staminaReduction)
	activate()


func getRelatedItems():
	return [ctx.item_book.getDescriptor("Flame")]

func _readyInit():
	._readyInit()
	pass
