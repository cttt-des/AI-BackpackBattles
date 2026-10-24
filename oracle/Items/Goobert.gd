extends Item
class_name Goobert

onready var goobertAnimation = $Icon / GoobertAnimation
onready var activationsToTrigger = getP1()

var activations: int


func logCooldown() -> bool:
	return true

func canAffect(item):
	return item.canActivate()

func prepare():
	activations = 0
	iterationCooldown = activationsToTrigger
	triggerTime = iterationCooldown
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)
	
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
		
		if doubleActivationChance > 0 and Util.flip(doubleActivationChance):
			doCooldownEffect()
			activate()
		
		showCooldownSmooth(activations / activationsToTrigger, true)
	else:
		showCooldownSmooth(activations / activationsToTrigger, false)
	
	triggerTime = activationsToTrigger - activations
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown, null, false, event)











