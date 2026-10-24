extends Item

onready var staminaReduction = - getP("stamina")

func onPrepare():
	for item in inventory.getItems():
		if item.isWeapon():
			item.changeStaminaFactor(staminaReduction)
