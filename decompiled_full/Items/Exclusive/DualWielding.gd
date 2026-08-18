extends Item

const activeTexture = preload("res://Items/Exclusive/Sprites/DualWielding_active.png")
const inactiveTexture = preload("res://Items/Exclusive/Sprites/DualWielding.png")

onready var weaponSpeed: = getP("speed") / 100.0
onready var weaponStamina: = getP("stamina")

var active: bool

func onItemAdded(item):
	.onItemAdded(item)
	checkItems()

func onItemRemoved(item):
	.onItemRemoved(item)
	checkItems()

func onRemoveFromInventory():
	active = false
	sprite.texture = inactiveTexture

func canAffect_global(item):
	return item.isWeapon() and item.getBaseStaminaCost() > 0

func checkItems():
	var numWeapons = 0
	for item in inventory.getItems():
		if canAffect_global(item):
			numWeapons += 1
	
	if numWeapons == 2:
		active = true
		sprite.texture = activeTexture
	else:
		active = false
		sprite.texture = inactiveTexture

func onPrepare():
	if active:
		for item in inventory.getItems():
			if item.hasType(Type.Weapon) and item.getBaseStaminaCost() > 0:
				item.addSpeed(weaponSpeed)
				item.changeStaminaFactor( - weaponStamina)
