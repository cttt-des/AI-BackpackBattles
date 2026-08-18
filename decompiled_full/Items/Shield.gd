extends Item
class_name Shield

var blockedDamageRes = null

func prepare():
	blockedDamageRes = null
	connectForCombat(character(), "pre_take_damage", "preTakeDamage")
	connectForCombat(character(), "character_attacked", "onCharacterAttacked")
	.prepare()

func getDamageBlock():
	return getP_m("damblock")

func beforeBlock():
	blockedDamageRes.applyDamageReduction(getDamageBlock(), self)

func afterBlock():
	pass

func canBlockDamageRes(damageRes: DamageResult) -> bool:
	return damageRes.triggerOnMeleeAttacked()

func preTakeDamage(damageRes: DamageResult):
	if canBlockDamageRes(damageRes) and rollChance():
		blockedDamageRes = damageRes
		beforeBlock()

func onCharacterAttacked(damageRes: DamageResult):
	if blockedDamageRes == damageRes:
		afterBlock()
		EventBus.emitSignal(self, "blocked", [blockedDamageRes])
		blockedDamageRes = null
		
