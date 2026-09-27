extends Item
var numFlames
var burningSwordDescr
var burningBladeDescr
var staminaReduction

func onPrepare():
	numFlames = countAllInInventoryOfType(ctx.item_book.getDescriptor("Flame"))
	
	for item in getAllInInventoryOfType(burningSwordDescr):
		item.changeStaminaFactor(staminaReduction)
	
	for item in getAllInInventoryOfType(burningBladeDescr):
		item.changeStaminaFactor(staminaReduction)


func doCooldownEffect():
	if numFlames > 0:
		giveHeat(getP("heat") * numFlames)
	onAfterEffectFinished()


func canAffect_global(item):
	return (item.isA(ctx.item_book.getDescriptor("Flame")) or 
			item.isA(burningBladeDescr) or 
			item.isA(burningSwordDescr))

func _readyInit():
	._readyInit()
	burningSwordDescr = ctx.item_book.getDescriptor("Burning Sword")
	burningBladeDescr = ctx.item_book.getDescriptor("Burning Blade")
	staminaReduction = - getP("stamina")
