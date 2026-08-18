extends Item
class_name RangerCollar

onready var acornAceDescriptor = ItemBook.getDescriptor("Acorn Ace")

var affectedItems

func prepare():
	affectedItems = getAffectedItems()
	var numAces = countAllInInventoryOfType(acornAceDescriptor)
	if numAces > 0:
		var staminaReduction = numAces * - acornAceDescriptor.getP("stamina")
		for item in affectedItems:
			item.changeStaminaFactor(staminaReduction)
	.prepare()
