extends Item
var speedUpItem = null
var speedTimer
var speedPerTrigger
var maxSpeed

func canAffect(item):
	return item.canActivate()


func canAffect_secondary(item):
	return item.hasCooldown()


func onPrepare():
	for item in getAffectedItems(CoreConst.Affected.Secondary):
		speedUpItem = item
	
	if speedUpItem != null:
		for triggerItem in getAffectedItems():
			connectForCombat(triggerItem, "activated", "onTriggerItemActivated")


func onTriggerItemActivated(event):
	var curSpeed = ctx.rope_speedups.get(speedUpItem, 0.0)
	var speedLeft = maxSpeed - curSpeed
	if speedLeft > 0:
		speedUpItem.addSpeed(min(speedLeft, speedPerTrigger))
	
	ctx.util.dictAdd(ctx.rope_speedups, speedUpItem, speedPerTrigger)
	speedTimer.start(getP_m("dur"))
	miniActivate()


func onSpeedTimeout():
	ctx.util.dictSub(ctx.rope_speedups, speedUpItem, speedPerTrigger)
	var curSpeed = ctx.rope_speedups.get(speedUpItem, 0.0)
	var speedLeft = maxSpeed - curSpeed
	if speedLeft > 0:
		speedUpItem.reduceSpeed(min(speedLeft, speedPerTrigger))


func onCombatEnd():
	speedTimer.stop()
	speedUpItem = null

func _readyInit():
	._readyInit()
	speedTimer = newItemTimer("SpeedTimer", "onSpeedTimeout", true)
	speedPerTrigger = getP("speed") / 100.0
	maxSpeed = getP("max") / 100.0
