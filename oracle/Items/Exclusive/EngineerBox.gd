extends Bag

onready var chargeTimer = $ChargeTimer
onready var delay: = getP("delay")
onready var chargeSpeed: = getP("speed") / 100.0

var queuedEmitters: = []

func onCombatEnd():
	chargeTimer.stop()
	queuedEmitters.clear()

func canApplyEffect(toItem):
	return toItem.has_method("emitCharge")

func onPrepare():
	for item in getAffectedItemsInside():
		EventBus.connectEvent(item, "charge_emitted", self, "onItemInsideEmittedCharge")
	
func onItemInsideEmittedCharge(item):
	queuedEmitters.push_back(item)
	chargeTimer.start(delay)

func onChargeTimerTimeout():
	var emitter = queuedEmitters.pop_front()
	emitter.emitCharge(chargeSpeed)
