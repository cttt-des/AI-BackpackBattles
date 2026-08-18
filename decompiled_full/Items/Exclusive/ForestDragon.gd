extends Weapon

onready var regen: = int(getP("regen"))
onready var luck: = int(getP("luck"))
onready var damPerRegen: = getP("dam")
onready var speedPerNature: = getP("speed") / 100.0

func canAffect(item):
	return item.hasType(Type.Nature)

func onPrepare():
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")
	addSpeed(speedPerNature * getNumAffectedItems())

func onRegenChanged(amount, event):
	changeVaryingDamage(amount * damPerRegen)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		giveRegeneration(regen)
		giveLucky(luck)
