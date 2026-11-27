extends Card
var quads = 0
var triplets = 0
var pairs = 0
var activationParticles
var staminaReduction
var revealsPerQuad

func countChain():
	quads = 0
	triplets = 0
	pairs = 0
	
	if chainPosition > 0:
		var counter = Dictionary()
		for i in chainPosition:
			ctx.util.dictAdd(counter, deck.cards[i].descriptor)
	
		for cardType in counter:
			quads += counter[cardType] / 4
			var rest = counter[cardType] %4
			triplets += rest / 3
			rest = rest % 3
			pairs += rest / 2


func notifyChainPosition(_deck, _chainPos, chainLength):
	.notifyChainPosition(_deck, _chainPos, chainLength)
	countChain()


func doRevealEffect():
	giveRandomBuffs(getP("buffs"))
	if pairs > 0:
		character().gainCritResistStacks(pairs)
	
	if triplets > 0:
		for item in inventory.getItems():
			
			item.changeStaminaFactor( - staminaReduction * triplets)
	
	if quads > 0:
		var legitCards = []
		for i in chainPosition:
			if deck.cards[i].descriptor != descriptor:
				legitCards.push_back(deck.cards[i])
		
		
		for i in quads * revealsPerQuad:
			if not legitCards.empty():
				var revealedCard = ctx.util.pickRandomElement(legitCards)
				revealedCard.doRevealEffect()
				if legitCards.size() > 1:
					legitCards.erase(revealedCard)
			
	activate()


func getCardDescription(descr) -> String:
	if deck:
		var counterText = ctx.util.tra("Joker_COUNTER")
		var state = CoreConst.StatModified.No
		if pairs > 0:
			state = CoreConst.StatModified.Positive
		else:
			state = CoreConst.StatModified.Negative
		counterText = insertParameter(counterText, "pairs", pairs, state, false)
		
		if triplets > 0:
			state = CoreConst.StatModified.Positive
		else:
			state = CoreConst.StatModified.Negative
		counterText = insertParameter(counterText, "triplets", triplets, state, false)
		
		if quads > 0:
			state = CoreConst.StatModified.Positive
		else:
			state = CoreConst.StatModified.Negative
		counterText = insertParameter(counterText, "quadruples", quads, state, false)
		
		descr += "\n" + counterText
		
	elif placed:
		descr += "\n" + ctx.util.wrapInColor(tr("CARD_HINT"), ctx.util.paramColor)
	
	return descr

func _readyInit():
	._readyInit()
	staminaReduction = getP("stamina")
	revealsPerQuad = int(getP("cards"))
