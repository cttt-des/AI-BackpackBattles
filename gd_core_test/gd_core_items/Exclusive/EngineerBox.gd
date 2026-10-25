extends Bag
var queuedEmitters: = []
var chargeTimer
var delay
var chargeSpeed

func onCombatEnd():
	chargeTimer.stop()
	queuedEmitters.clear()


func canApplyEffect(toItem):
	return toItem.has_method("emitCharge")


func onPrepare():
	for item in getAffectedItemsInside():
		ctx.bus.connectEvent(item, "charge_emitted", self, "onItemInsideEmittedCharge")
	

func onItemInsideEmittedCharge(item):
	queuedEmitters.push_back(item)
	chargeTimer.start(delay)


func onChargeTimerTimeout():
	var emitter = queuedEmitters.pop_front()
	emitter.emitCharge(chargeSpeed)

func _readyInit():
	._readyInit()
	chargeTimer = newItemTimer("ChargeTimer", "onChargeTimerTimeout", true)
	delay = getP("delay")
	chargeSpeed = getP("speed") / 100.0
