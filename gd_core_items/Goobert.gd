extends Item
class_name Goobert
var activations: int
var goobertAnimation
var activationsToTrigger

func logCooldown() -> bool:
	return true


func canAffect(item):
	return item.canActivate()


func prepare():
	activations = 0
	iterationCooldown = activationsToTrigger
	triggerTime = iterationCooldown
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)
	
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")
	.prepare()


func doCooldownEffect():
	heal()


func onItemActivated(event):
	activations += 1
	
	if activations == getP1():
		activations = 0
		doCooldownEffect()
		activate()
		
		if doubleActivationChance > 0 and ctx.util.flip(doubleActivationChance):
			doCooldownEffect()
			activate()
		
		showCooldownSmooth(activations / activationsToTrigger, true)
	else:
		showCooldownSmooth(activations / activationsToTrigger, false)
	
	triggerTime = activationsToTrigger - activations
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown, null, false, event)











func _readyInit():
	._readyInit()
	activationsToTrigger = getP1()
