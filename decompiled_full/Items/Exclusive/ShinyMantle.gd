extends Item

const activationPulse = preload("res://Items/Animations/BookOfLightActivationPulse.tscn")

onready var activationParticles = $ActivationParticles
onready var buffTimer = $BuffTimer
onready var blind: = int(getP("blind"))
onready var manaNeeded_base: = int(getP("manat"))
onready var manaCostIncrease: = int(getP("mana"))
onready var maxUses: = int(getP("max"))


var invuProcced: int
var gemDurFactor: float
var manaNeeded

func canAffect(item):
	return not item.isBag()

func _ready():
	CraftingManager.connect("recipes_updated", self, "findBondsWithAffectedItems")






func readyToFuse() -> bool:
	return not bondedIngredients.empty()

func onFusingFinished(validBonds):
	.onFusingFinished(validBonds)
	
	var value: = 0
	for item in validBonds:
		value += item.getPrice()
	
	
	while value > 0:
		for rarity in range(Rarity.Godly, Rarity.Common - 1, - 1):
			var descr = ItemBook.getGemOfRarity(rarity)
			if value >= descr.getPrice():
				value -= descr.getPrice()
				ItemBook.generateAndStorageItem(descr, global_position)
	
	activate()
	Game.saveRunState()

func getCounterValue() -> int:
	var gold = 0
	var inv = inventory if placed else Game.PLAYER.INVENTORY
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
		Util.createPulse(activationPulse, self, global_position)
	
		if invuProcced == maxUses:
			onAfterEffectFinished()
			return
	
	activate()





func onInvuStarted(event):
	inflictBlind(blind, event)
	
	
	






func onStateChanged(invuActive):
	if invuActive:
		activationParticles.activate()
	else:
		activationParticles.deactivate()

func buffEnded():
	setState(false)

func onCombatEnd():
	buffTimer.stop()

func onShopEntered():
	onStateChanged(false)
