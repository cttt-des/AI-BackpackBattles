extends Item
const chargeCells1 = [Vector2( - 1, - 1), Vector2( - 2, - 1), Vector2( - 2, 0), Vector2( - 2, 1), Vector2( - 3, 1), Vector2( - 4, 1), Vector2( - 4, 0)]
const chargeCells2 = [Vector2( - 1, - 1), Vector2(0, - 1), Vector2(0, - 2), Vector2(0, - 3), Vector2(1, - 3), Vector2(2, - 3), Vector2(2, - 2)]
var hasActivated: bool
var heatNeeded
var luck

func onPrepare():
	hasActivated = false


func doCooldownEffect():
	if character().getHeat() >= heatNeeded:
		var event = useHeat(heatNeeded)
		giveLucky(luck, event)
		giveBlock(getBlock(), true, event)
	
	onAfterEffectFinished()


func canAffect_lightning(item):
	return item.gainsBuffs() or item.reactsToCharges()


func onChargeReceived(_charge):
	if not hasActivated:
		hasActivated = true
		emitCharge()
		ctx.bus.emitSignal(self, "charge_emitted", [self])


func emitCharge(speedFactor = 1.0):
	var event = activate()
	sendCharge(getP_m("dur"), chargeCells1, speedFactor, event)
	sendCharge(getP_m("dur"), chargeCells2, speedFactor, event)



func onChargeEnteredCell(charge, cellIndex):
	changeChargedItemStat(charge, cellIndex, getChance(), getChance2())


func chargedItemStatChange(item, value):
	item.changeAmplificiationChancePercent_allBuffs(value)

func _readyInit():
	._readyInit()
	heatNeeded = int(getP("heatt"))
	luck = int(getP("luck"))
