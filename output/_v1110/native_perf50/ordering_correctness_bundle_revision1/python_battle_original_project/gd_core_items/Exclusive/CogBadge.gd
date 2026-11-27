extends Item
const chargeCells = [
	Vector2( - 1, - 1), Vector2( - 1, - 2), Vector2( - 1, - 3), Vector2( - 1, - 4), 
	Vector2( - 2, - 3), Vector2( - 3, - 2), Vector2( - 4, - 1), Vector2( - 3, 0), 
	Vector2( - 2, 1), Vector2( - 1, 2), Vector2(0, 1), Vector2(1, 0), 
	Vector2(2, - 1), Vector2(1, - 2)]
var flatSpeed
var speedPerTile
var cogDescriptor

func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass

func onShopEntered():
	pass

func canAffect_lightning(item):
	return item.hasCooldown() or item.reactsToCharges()


func doCooldownEffect():
	emitCharge()
	ctx.bus.emitSignal(self, "charge_emitted", [self])
	onAfterEffectFinished(false)


func emitCharge(speedFactor = 1.0):
	var event = activate()
	sendCharge(getP_m("dur"), chargeCells, speedFactor, event)


func onChargeEnteredCell(charge, cellIndex):
	changeChargedItemStat(charge, cellIndex, flatSpeed, speedPerTile)


func chargedItemStatChange(item, value):
	item.addSpeed(value)


func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 3

func _readyInit():
	._readyInit()
	flatSpeed = getP("speed") / 100
	speedPerTile = getP("speed2") / 100
	cogDescriptor = ctx.item_book.getDescriptor("Cog")
