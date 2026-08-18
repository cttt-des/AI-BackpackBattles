extends Item

var cards = []
var cardActivations = 0
var chainStarted: bool

onready var connector = $Connector




func canAffect(item):
	return item.hasType(Type.Card)

func onAddToInventory():
	updateCards()

func onRemoveFromInventory():
	resetChain()
	connector.disappear()
	connector.call_deferred("checkState")

func resetChain():
	for card in cards:
		card.notifyChainPosition(self, - 1, cards.size())
	cards.clear()


func countDuplicates(untilCardIndex) -> int:
	var descriptors = []
	for i in untilCardIndex:
		descriptors.push_back(cards[i].descriptor)
	return Util.countDuplicates(descriptors)

func updateCards():
	resetChain()
	var affected = getAffectedItems()
	if not affected.empty():
		cards.push_back(affected[0])
		connector.appear()
		connector.call_deferred("checkState")
		
		var nextCard = cards[0].getNextCard()
		while (nextCard and not nextCard in cards):
			cards.push_back(nextCard)
			nextCard = nextCard.getNextCard()
	else:
		connector.disappear()
		connector.call_deferred("checkState")

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

func getGatedDescriptor(rarity) -> ItemDescriptor:
	var itemName: String
	match rarity:
		Rarity.Common:
			itemName = "The Lovers"
		Rarity.Rare:
			if Game.showExclusiveContent() and Util.flip(0.5):
				itemName = "Reverse"
			else:
				itemName = "Ace of Spades"
		Rarity.Epic:
			if Util.flip(0.3):
				itemName = "The Fool"
			else:
				itemName = "White-Eyes Blue Dragon"
		Rarity.Legendary:
			itemName = "Holo Fire Lizard"
		Rarity.Godly:
			if Game.showExclusiveContent() and Util.flip(0.5):
				itemName = "Joker"
			else:
				itemName = "Darkest Lotus"
	return ItemBook.getDescriptor(itemName)

func getRelatedItemColumns() -> int:
	return 4

func getRelatedItemHeight() -> int:
	return 120
