extends Item
class_name RangerCollar
var affectedItems
var acornAceDescriptor

func prepare():
	affectedItems = getAffectedItems()
	var numAces = countAllInInventoryOfType(acornAceDescriptor)
	if numAces > 0:
		var staminaReduction = numAces * - acornAceDescriptor.getP("stamina")
		for item in affectedItems:
			item.changeStaminaFactor(staminaReduction)
	.prepare()

func _readyInit():
	._readyInit()
	acornAceDescriptor = ctx.item_book.getDescriptor("Acorn Ace")
