extends Item
var maxUses: int
var uses: int
var coldAmount

func canAffect(item):
	return item.hasType(CoreConst.Type.Ice) and not item.isA(descriptor)


func onPrepare():
	uses = 0
	maxUses = int(getP1()) + getNumAffectedItems()


func doCooldownEffect():
	if uses < maxUses:
		uses += 1
		var dam = descriptor.minDam
		var damageRes = dealEffectDamage(dam)
		giveStacksTemporary(opponent(), CoreConst.EventType.Cold, 
			coldAmount, getP_m("dur_cold"), damageRes.event)
		if uses == maxUses:
			onAfterEffectFinished()
		else:
			activate()

func _readyInit():
	._readyInit()
	coldAmount = int(getP3())
	damageSource = CoreDamageSource.new().setItem(self)

