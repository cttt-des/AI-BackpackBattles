extends "res://Items/Exclusive/Squirrel.gd"

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		stealRandomBuff(1)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		var res = dealDamage()
		activate(res)
