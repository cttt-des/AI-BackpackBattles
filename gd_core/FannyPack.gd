extends Bag
var speedBonus

func onCombatStart():
	var active = false
	var totalSpeed = speedBonus
	if isTypeInInventory(ctx.item_book.getDescriptor("Bagtacular")):
		totalSpeed += ctx.item_book.getDescriptor("Bagtacular").getP("speed") / 100.0
	
	for item in getItemsInside():
		if canApplyEffect(item):
			item.addSpeed(totalSpeed)
			active = true
	
	if active:
		activate()


func canApplyEffect(toItem):
	return toItem.hasCooldown() and not toItem.isBag()

func _readyInit():
	._readyInit()
	speedBonus = getP1() / 100
