extends "res://gd_core_items/Exclusive/Squirrel.gd"

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		stealRandomBuff(1)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		var res = dealDamage()
		activate(res)

func _readyInit():
	._readyInit()
	damageSource = CoreDamageSource.new().setItem(self)

