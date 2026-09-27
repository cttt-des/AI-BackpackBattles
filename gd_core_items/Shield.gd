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


func canBlockDamageRes(damageRes: CoreDamageResult) -> bool:
	return damageRes.triggerOnMeleeAttacked()


func preTakeDamage(damageRes: CoreDamageResult):
	if canBlockDamageRes(damageRes) and rollChance():
		blockedDamageRes = damageRes
		beforeBlock()


func onCharacterAttacked(damageRes: CoreDamageResult):
	if blockedDamageRes == damageRes:
		afterBlock()
		ctx.bus.emitSignal(self, "blocked", [blockedDamageRes])
		blockedDamageRes = null
		

func _readyInit():
	._readyInit()
	pass
