extends Item

onready var burningSwordDescr = ItemBook.getDescriptor("Burning Sword")
onready var burningBladeDescr = ItemBook.getDescriptor("Burning Blade")

var numFlames
onready var staminaReduction = - getP("stamina")

func onPrepare():
	numFlames = countAllInInventoryOfType(ItemBook.flameDescriptor)
	
	for item in getAllInInventoryOfType(burningSwordDescr):
		item.changeStaminaFactor(staminaReduction)
	
	for item in getAllInInventoryOfType(burningBladeDescr):
		item.changeStaminaFactor(staminaReduction)

func doCooldownEffect():
	if numFlames > 0:
		giveHeat(getP("heat") * numFlames)
	onAfterEffectFinished()

func canAffect_global(item):
	return (item.isA(ItemBook.flameDescriptor) or 
			item.isA(burningBladeDescr) or 
			item.isA(burningSwordDescr))
