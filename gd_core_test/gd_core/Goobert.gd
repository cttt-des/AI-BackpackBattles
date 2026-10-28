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
	# ★ np25 诊断（受控，双门控零耗链）：Goobert 计数器入口——接收者/计数/
	#   阈值/触发源（对拍 py 侧无 TRIG doCooldownEffect 串扰，run874_r7）。
	var _gsrc = "?"
	if event != null and event.origin != null:
		_gsrc = String(event.origin.name)
	ctx.rng.trace_diag("GACT", String(descriptor.identifier) + "/ot" + str(int(ownerType)), str(activations + 1) + "/" + str(getP1()), "src=" + _gsrc)
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
