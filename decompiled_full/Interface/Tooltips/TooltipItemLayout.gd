extends Control

const MARGIN = 20
var addedItems = []

func addItem(descriptor, maxSize, tooltip, defaultScaling = 0.7):
	var ingredient = descriptor.instantiate_pooled()
	ingredient.ownerType = ingredient.Owner.Tooltip
	add_child(ingredient)
	ingredient.initTooltip()
	ingredient.scaleToFit(maxSize, defaultScaling)
	ingredient.owningBuildIntoRecipesTooltip = tooltip
	return ingredient

func enableFocus():
	for node in addedItems:
		if not node is Control:
			node.enableFocus()
			node.enableTooltip()
			node.showClickArea()

func discard():
	
	for node in addedItems:
		if not node is Control:
			node.owningBuildIntoRecipesTooltip = null
			node.discard()
