extends Bag

onready var damBonusFactor = getP("bonusdam") / 100.0
onready var staminaReduction = getP("stamina")

func canApplyEffect(toItem):
	return toItem.isWeapon()

func doCooldownEffect():
	for item in getAffectedItemsInside():
		if item.canBeEmpowered():
			item.addBonusDamageFactor(damBonusFactor)
		item.changeStaminaFactor( - staminaReduction)
	activate()
