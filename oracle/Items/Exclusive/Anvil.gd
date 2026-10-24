extends Item

func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	.addToInventory(_inventory, _occupiedCells, _placedByPlayer)
	Game.connect("item_crafted", self, "onCraft")

func onRemoveFromInventory():
	Game.disconnect("item_crafted", self, "onCraft")

func onCraft(_itemDescriptor):
	var flame = ItemBook.generateItem("Flame")
	placeGeneratedItem(flame, inventory.getAdjacentCells(occupiedCells))
	
	activate(null, false)
	Game.saveRunState()

func canAffect(item):
	return item.isCrafted()

func canAffect_secondary(item):
	return item.isWeapon()

func onPreCombatStart():
	var numCrafted = getAffectedItems().size()
	if numCrafted > 0:
		var bonusDamage = getP1() * numCrafted
		var staminaReduction = - getP2() * numCrafted
		for affectedWeapon in getAffectedItems(Affected.Secondary):
			if affectedWeapon.canBeEmpowered():
				affectedWeapon.addBonusDamage(bonusDamage)
				var event = Game.combatLog.createEvent_DamageBuff(self, affectedWeapon, bonusDamage, character().playerId)
				EventBus.logEvent(event)
			
			affectedWeapon.changeStaminaFactor(staminaReduction)
	activate()

func getRelatedItems():
	return [ItemBook.flameDescriptor]
