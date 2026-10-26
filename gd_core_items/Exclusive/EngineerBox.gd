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
	# ★ np24：录制镜像（gd_core/CoreContext.gd eb_relay_mirrored）——录制侧 EB
	#   ChargeTimer 首弹后队列不推进（探针实证 fire=1 次/侧、ts=0），接力重发射
	#   =0；gd 侧 CoreTimer 级联=接力活跃（sendCharge +10）。镜像=连接环不建。
	if ctx != null and ctx.eb_relay_mirrored:
		return
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
