extends Bag
var damBonusFactor
var staminaReduction

func canApplyEffect(toItem):
	return toItem.isWeapon()


func doCooldownEffect():
	for item in getAffectedItemsInside():
		if item.canBeEmpowered():
			item.addBonusDamageFactor(damBonusFactor)
		item.changeStaminaFactor( - staminaReduction)
	activate()

func _readyInit():
	._readyInit()
	damBonusFactor = getP("bonusdam") / 100.0
	staminaReduction = getP("stamina")
