extends Item
var active: bool
var weaponSpeed
var weaponStamina

func onItemAdded(item):
	.onItemAdded(item)
	checkItems()


func onItemRemoved(item):
	.onItemRemoved(item)
	checkItems()


func onRemoveFromInventory():
	active = false


func canAffect_global(item):
	return item.isWeapon() and item.getBaseStaminaCost() > 0


func checkItems():
	var numWeapons = 0
	for item in inventory.getItems():
		if canAffect_global(item):
			numWeapons += 1
	
	if numWeapons == 2:
		active = true
	else:
		active = false


func onPrepare():
	if active:
		for item in inventory.getItems():
			if item.hasType(CoreConst.Type.Weapon) and item.getBaseStaminaCost() > 0:
				item.addSpeed(weaponSpeed)
				item.changeStaminaFactor( - weaponStamina)

func _readyInit():
	._readyInit()
	weaponSpeed = getP("speed") / 100.0
	weaponStamina = getP("stamina")
