extends Weapon
var staminaReduction

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		changeStaminaFactor( - staminaReduction)
		if rollChance():
			stealRandomBuff(1)

func _readyInit():
	._readyInit()
	staminaReduction = getP("stamina")
