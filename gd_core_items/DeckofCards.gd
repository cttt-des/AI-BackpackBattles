extends Item
var cards = []
var cardActivations = 0
var chainStarted: bool
var connector

func canAffect(item):
	return item.hasType(CoreConst.Type.Card)


func onAddToInventory():
	updateCards()


func onRemoveFromInventory():
	resetChain()


func resetChain():
	for card in cards:
		card.notifyChainPosition(self, - 1, cards.size())
	cards.clear()



func countDuplicates(untilCardIndex) -> int:
	var descriptors = []
	for i in untilCardIndex:
		descriptors.push_back(cards[i].descriptor)
	return ctx.util.countDuplicates(descriptors)


func updateCards():
	resetChain()
	var affected = getAffectedItems()
	if not affected.empty():
		cards.push_back(affected[0])
		
		var nextCard = cards[0].getNextCard()
		while (nextCard and not nextCard in cards):
			cards.push_back(nextCard)
			nextCard = nextCard.getNextCard()
	else:
		pass

	var chainLength = cards.size()
	
	for i in chainLength:
		cards[i].notifyChainPosition(self, i, chainLength)


func onItemAdded(item):
	.onItemAdded(item)
	if item is Card:
		updateCards()


func onItemRemoved(item):
	.onItemRemoved(item)
	if item is Card:
		updateCards()


func onPrepare():
	chainStarted = false


func onCombatStart():
	giveLucky(getP1())
	if not chainStarted:
		chainStarted = true
		cardActivations = 0
		if not cards.empty():
			
			cards[0].call_deferred("startActivation")
	activate()


func notifyActivation():
	cardActivations += 1


func getGatedDescriptor(rarity) -> CoreItemData:
	return null

func getRelatedItemColumns() -> int:
	return 4


func getRelatedItemHeight() -> int:
	return 120

func _readyInit():
	._readyInit()
	pass
