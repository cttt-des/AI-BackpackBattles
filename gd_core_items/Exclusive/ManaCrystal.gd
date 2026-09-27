extends Item
const chargeCells = [
	[Vector2(0, 0), Vector2( - 1, 0), Vector2( - 2, 0), Vector2( - 3, 0)], 
	[Vector2(0, 0), Vector2(0, - 1), Vector2(0, - 2)], 
	[Vector2(0, 0), Vector2(1, 0), Vector2(2, 0), Vector2(3, 0)], 
	[Vector2(0, 0), Vector2(0, 1), Vector2(0, 2)]
	]
var mana1
var mana2

func canAffect_lightning(item):
	return true


func doCooldownEffect():
	emitCharge()
	ctx.bus.emitSignal(self, "charge_emitted", [self])


func emitCharge(speedFactor = 1.0):
	var event = activate()
	for i in chargeCells.size():
		sendCharge(getP_m("dur"), chargeCells[i], speedFactor, event)


func onChargeEnteredCell(charge, cellIndex):
	if (charge.curChargedItem != null and 
		charge.curChargedItem != charge.lastChargedItem):
		
		if charge.curChargedItem.hasType(CoreConst.Type.Magic):
			giveMana(mana2)
		else:
			giveMana(mana1)
	

func _readyInit():
	._readyInit()
	mana1 = int(getP("mana1"))
	mana2 = int(getP("mana2"))
