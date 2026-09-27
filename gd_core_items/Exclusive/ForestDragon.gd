extends Weapon
var regen
var luck
var damPerRegen
var speedPerNature

func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


func onPrepare():
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")
	addSpeed(speedPerNature * getNumAffectedItems())


func onRegenChanged(amount, event):
	changeVaryingDamage(amount * damPerRegen)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		giveRegeneration(regen)
		giveLucky(luck)

func _readyInit():
	._readyInit()
	regen = int(getP("regen"))
	luck = int(getP("luck"))
	damPerRegen = getP("dam")
	speedPerNature = getP("speed") / 100.0
