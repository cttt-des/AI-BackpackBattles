extends Item
class_name Card
export (Texture) var back
export (Texture) var activeFront
var curActivationDelay: float
var faceUp = true
var activating = false
var chainPosition = - 1
var deck = null
var cardAnimation
var front
var connector
var notInChainMark

func setFaceUp():
	if not faceUp:
		faceUp = true


func setFaceDown():
	if faceUp:
		faceUp = false


func updateTexture():
	if faceUp:
		if deck and activeFront and cardSecondaryEffectActive():
			pass
		else:
			pass
	else:
		pass


func cardSecondaryEffectActive():
	return false


func canAffect(item):
	if placed:
		return (deck and 
			item.hasType(CoreConst.Type.Card) and 
			(item.chainPosition > chainPosition or item.chainPosition == - 1))
	else:
		return item.hasType(CoreConst.Type.Card) and not item.deck
	

func prepare():
	.prepare()
	setState(false)


func preCombatStart():
	.preCombatStart()
	deactivateCooldown()


func getNextCard():
	
	
	var affected = getItemsInAffectedCells_cached()
	if not affected.empty() and affected[0].hasType(CoreConst.Type.Card):
		return affected[0]
	else:
		return null


func startActivation():
	if activating or faceUp: return
	
	activating = true
	iterationCooldown = getCooldown()
	triggerTime = iterationCooldown
	activateCooldown()
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)



func playActivationAnimation(aniType = descriptor.activationAni, 
	consume: bool = false):
	pass
	


func onStateChanged(_faceUp: bool):
	if _faceUp:
		
		if faceUp:
			pass
		else:
			pass
	else:
		if faceUp:
			pass
	
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


func onRemoveFromInventory():
	deck = null
	updateTexture()
	


func notifyChainPosition(_deck, _chainPos, chainLength):
	chainPosition = _chainPos

	if chainPosition == - 1:
		deck = null
		if placed:
			pass
	else:
		deck = _deck
		
		if chainPosition != chainLength - 1:
			pass
		else:
			pass
	
	updateTexture()
	


func getDescription(wrapInColor = true) -> String:
	var descr = .getDescription(wrapInColor)
	return getCardDescription(descr)


func getCardDescription(descr) -> String:
	if deck:
		descr += "\n\n" + insertParameter(ctx.util.tra("CARD_COUNT"), "num", chainPosition, CoreConst.StatModified.No, false)
	elif placed:
		descr += "\n\n" + ctx.util.wrapInColor(ctx.util.tra("CARD_HINT"), ctx.util.paramColor)
	
	return descr

func _readyInit():
	._readyInit()
	pass
