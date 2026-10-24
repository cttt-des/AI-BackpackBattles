extends Item

onready var speedTimer = $SpeedTimer
onready var speedPerTrigger: = getP("speed") / 100.0
onready var maxSpeed: = getP("max") / 100.0
var speedUpItem = null

func canAffect(item):
	return item.canActivate()

func canAffect_secondary(item):
	return item.hasCooldown()

func onPrepare():
	for item in getAffectedItems(Affected.Secondary):
		speedUpItem = item
	
	if speedUpItem != null:
		for triggerItem in getAffectedItems():
			connectForCombat(triggerItem, "activated", "onTriggerItemActivated")

func onTriggerItemActivated(event):
	var curSpeed = Game.ropeSpeedups.get(speedUpItem, 0.0)
	var speedLeft = maxSpeed - curSpeed
	if speedLeft > 0:
		speedUpItem.addSpeed(min(speedLeft, speedPerTrigger))
	
	Util.dictAdd(Game.ropeSpeedups, speedUpItem, speedPerTrigger)
	speedTimer.start(getP_m("dur"))
	miniActivate()

func onSpeedTimeout():
	Util.dictSub(Game.ropeSpeedups, speedUpItem, speedPerTrigger)
	var curSpeed = Game.ropeSpeedups.get(speedUpItem, 0.0)
	var speedLeft = maxSpeed - curSpeed
	if speedLeft > 0:
		speedUpItem.reduceSpeed(min(speedLeft, speedPerTrigger))

func onCombatEnd():
	speedTimer.stop()
	speedUpItem = null
