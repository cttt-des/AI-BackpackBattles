extends Item
var invuProcced: int
var gemDurFactor: float
var manaNeeded
var activationParticles
var buffTimer
var blind
var manaNeeded_base
var manaCostIncrease
var maxUses

func canAffect(item):
	return not item.isBag()


func readyToFuse() -> bool:
	return not bondedIngredients.empty()


func onFusingFinished(validBonds):
	.onFusingFinished(validBonds)

func getCounterValue() -> int:
	var gold = 0
	var inv = inventory if placed else ctx.player.INVENTORY
	for item in inv.getItemsAndGems():
		if item.isGem():
			gold += item.getPrice()
	
	if dragged:
		for gem in getGemsNoNull():
			gold += gem.getPrice()
	
	return gold


func onPrepare():
	connectForCombat(character(), "character_invulnerable_start", "onInvuStarted")
	
	
	
	manaNeeded = manaNeeded_base
	invuProcced = 0
	gemDurFactor = floor(getCounterValue() / getP("gold"))
	setState(false)




func doCooldownEffect():
	if character().isVulnerable() and character().getMana() >= manaNeeded:
		setState(true)
		invuProcced += 1
		var invuDur = getP_m("dur_base") + getP_m("dur_bonus") * gemDurFactor
		buffTimer.start(invuDur)
		var event = character().makeInvulnerable(invuDur, self)
		useMana(manaNeeded, event)
		manaNeeded += manaCostIncrease
	
		if invuProcced == maxUses:
			onAfterEffectFinished()
			return
	
	activate()






func onInvuStarted(event):
	inflictBlind(blind, event)
	
	
	







func onStateChanged(invuActive):
	if invuActive:
		pass
	else:
		pass


func buffEnded():
	setState(false)


func onCombatEnd():
	buffTimer.stop()


func onShopEntered():
	onStateChanged(false)

func _readyInit():
	._readyInit()
	buffTimer = newItemTimer("BuffTimer", "buffEnded", false)
	blind = int(getP("blind"))
	manaNeeded_base = int(getP("manat"))
	manaCostIncrease = int(getP("mana"))
	maxUses = int(getP("max"))
