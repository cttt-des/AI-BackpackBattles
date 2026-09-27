extends Shield
var blockAcc: int
var bonusDamagePerTick: int
var damagePerTick: int
var blockPerTick: int
var activationParticles

func canAffect(item):
	return item.canBlock()


func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "gave_block", "onItemGaveBlock")
	bonusDamagePerTick = 0


func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	activate()


func onItemGaveBlock(amount, event):
	blockAcc += amount
	var ticks = blockAcc / blockPerTick
	if ticks > 0:
		blockAcc %= blockPerTick
		var dam = ticks * (damagePerTick + bonusDamagePerTick)
		var damageRes = dealEffectDamage(dam, event)
		miniActivate()




func canBlockDamageRes(damageRes: CoreDamageResult) -> bool:
	return damageRes.triggerOnAttacked()


func addBonusDamageOnTick(dam):
	bonusDamagePerTick += dam

func _readyInit():
	._readyInit()
	damagePerTick = getP4()
	blockPerTick = getP3()
	damageSource = CoreDamageSource.new().setItem(self)
	damageSource.unsetFlag(CoreDamageSource.Flags.CanCrit)
	
