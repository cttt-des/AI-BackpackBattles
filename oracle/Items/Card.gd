extends Item
class_name Card

export (Texture) var back
export (Texture) var activeFront

onready var cardAnimation = $CardAnimation
onready var front = sprite.texture
onready var connector = $Connector
onready var notInChainMark = $NotInChainMark

var curActivationDelay: float
var faceUp = true
var activating = false
var chainPosition = - 1
var deck = null





func setFaceUp():
	if not faceUp:
		faceUp = true
		cardAnimation.play("ShowBack")

func setFaceDown():
	if faceUp:
		faceUp = false
		cardAnimation.play("ShowBack")

func updateTexture():
	if faceUp:
		if deck and activeFront and cardSecondaryEffectActive():
			setTexture(activeFront)
		else:
			setTexture(front)
	else:
		setTexture(back)

func cardSecondaryEffectActive():
	return false

func canAffect(item):
	if placed:
		return (deck and 
			item.hasType(Type.Card) and 
			(item.chainPosition > chainPosition or item.chainPosition == - 1))
	else:
		return item.hasType(Type.Card) and not item.deck
	
func prepare():
	.prepare()
	setState(false)

func preCombatStart():
	.preCombatStart()
	deactivateCooldown()

func getNextCard():
	
	
	var affected = getItemsInAffectedCells_cached()
	if not affected.empty() and affected[0].hasType(Type.Card):
		return affected[0]
	else:
		return null

func startActivation():
	if activating or faceUp: return
	
	activating = true
	iterationCooldown = getCooldown()
	triggerTime = iterationCooldown
	activateCooldown()
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)


func playActivationAnimation(aniType = descriptor.activationAni, 
	consume: bool = false):
	
	animation.play("Activate")

func onStateChanged(_faceUp: bool):
	if _faceUp:
		
		if faceUp:
			cardAnimation.play("JokerReveal")
		else:
			cardAnimation.play("Reveal")
	else:
		if faceUp:
			cardAnimation.play("ShowBack")
	
	faceUp = _faceUp

func doRevealEffect():
	pass

func trigger():
	activating = false
	showCooldown(0)
	var nextCard = getNextCard()
	if nextCard:
		nextCard.startActivation()
	
	triggerTime = iterationCooldown
	
	setState(true, true)
	deactivateCooldown()
	doRevealEffect()
	


func combatEnd():
	.combatEnd()
	activating = false

func shopEntered(craft: bool):
	.shopEntered(craft)
	setFaceUp()

func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	.addToInventory(_inventory, _occupiedCells, _placedByPlayer)
	notInChainMark.appear()

func onRemoveFromInventory():
	notInChainMark.disappear()
	deck = null
	updateTexture()
	

func notifyChainPosition(_deck, _chainPos, chainLength):
	chainPosition = _chainPos

	if chainPosition == - 1:
		deck = null
		connector.disappear()
		if placed:
			notInChainMark.appear()
	else:
		deck = _deck
		notInChainMark.disappear()
		
		if chainPosition != chainLength - 1:
			connector.appear()
		else:
			connector.disappear()
	
	updateTexture()
	
	connector.call_deferred("checkState")

func getDescription(wrapInColor = true) -> String:
	var descr = .getDescription(wrapInColor)
	return getCardDescription(descr)

func getCardDescription(descr) -> String:
	if deck:
		descr += "\n\n" + insertParameter(Util.tra("CARD_COUNT"), "num", chainPosition, StatModified.No, false)
	elif placed:
		descr += "\n\n" + Util.wrapInColor(Util.tra("CARD_HINT"), Util.paramColor)
	
	return descr
