extends Item
var staminaReduction

func onPrepare():
	for item in inventory.getItems():
		if item.isWeapon():
			item.changeStaminaFactor(staminaReduction)

func _readyInit():
	._readyInit()
	staminaReduction = - getP("stamina")
