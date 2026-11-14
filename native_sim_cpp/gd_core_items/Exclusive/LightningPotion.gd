extends Potion
var blind
var lightningAni

func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Holy)


func onTriggerPotion(triggerEvent = null):
	var dam = descriptor.minDam
	var res = dealEffectDamage(dam)
	
	
	giveStacksTemporary(opponent(), CoreConst.EventType.Blind, 
		blind, getP_m("dur_blind"), triggerEvent)
	
	heal(getP_m("heal") * getNumAffectedItems(CoreConst.Affected.Secondary))


func onPrepare():
	baseCooldownOverride = ctx.rng.randf_range(
		getBaseCooldownIndex(0), getBaseCooldownIndex(1))

	


func doCooldownEffect():
	consumePotion(null, false)
	onAfterEffectFinished()


func fill():
	.fill()


func empty():
	.empty()

func _readyInit():
	._readyInit()
	blind = int(getP("blind"))
	damageSource = CoreDamageSource.new().setItem(self)

