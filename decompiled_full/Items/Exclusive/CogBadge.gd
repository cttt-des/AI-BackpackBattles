extends Item

const chargeCells = [
	Vector2( - 1, - 1), Vector2( - 1, - 2), Vector2( - 1, - 3), Vector2( - 1, - 4), 
	Vector2( - 2, - 3), Vector2( - 3, - 2), Vector2( - 4, - 1), Vector2( - 3, 0), 
	Vector2( - 2, 1), Vector2( - 1, 2), Vector2(0, 1), Vector2(1, 0), 
	Vector2(2, - 1), Vector2(1, - 2)]


onready var flatSpeed: = getP("speed") / 100
onready var speedPerTile: = getP("speed2") / 100

onready var cogDescriptor = ItemBook.getDescriptor("Cog")

func onAddToInventory():
	ItemBook.updateClass(self)

func onRemoveFromInventory():
	ItemBook.updateClass(self)

func onShopEntered():
	var cog = ItemBook.generateItem(cogDescriptor)
	var adjacentCells = inventory.getAdjacentCells(occupiedCells)
	placeGeneratedItem(cog, adjacentCells)
	activate()
	Game.saveRunState()

func canAffect_lightning(item):
	return item.hasCooldown() or item.reactsToCharges()

func doCooldownEffect():
	emitCharge()
	EventBus.emitSignal(self, "charge_emitted", [self])
	onAfterEffectFinished(false)

func emitCharge(speedFactor = 1.0):
	var event = activate()
	sendCharge(getP_m("dur"), chargeCells, speedFactor, event)

func onChargeEnteredCell(charge, cellIndex):
	changeChargedItemStat(charge, cellIndex, flatSpeed, speedPerTile)

func chargedItemStatChange(item, value):
	item.addSpeed(value)

func getRelatedItems():
	return ItemBook.getShopItemsForClass(Game.Classes_Full.Engineer)

func getRelatedItemColumns() -> int:
	return 3
