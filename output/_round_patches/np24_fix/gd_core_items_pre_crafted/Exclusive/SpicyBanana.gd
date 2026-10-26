extends Item
var staminaUsed: float
var boostedBananas: = 0
var bananaDescriptor
var manananaDescriptor
var heatPerActivation
var staminaForHeal

func canAffect(item):
	return item.isA(bananaDescriptor) or item.isA(manananaDescriptor)


func onBought():
	boostedBananas = 3


func getData():
	return boostedBananas


func setData(data):
	if data != null:
		boostedBananas = data


func onPrepare():
	
	for banana in getAffectedItems():
		connectForCombat(banana, "activated", "onBananaActivated")
	
	staminaUsed = 0
	connectForCombat(character(), "character_used_stamina", "onStaminaUsed")
	

func onBananaActivated(event):
	if rollChance():
		giveHeat(heatPerActivation, event)
		activate()


func onStaminaUsed(amount):
	staminaUsed += amount
	var healTicks = floor(staminaUsed / staminaForHeal)
	if healTicks > 0:
		heal(healTicks * getP_m("heal"))
		staminaUsed -= healTicks * staminaForHeal
		miniActivate()


func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr == bananaDescriptor:
		boostedBananas -= 1

func _readyInit():
	._readyInit()
	bananaDescriptor = ctx.item_book.getDescriptor("Banana")
	manananaDescriptor = ctx.item_book.getDescriptor("Mananana")
	heatPerActivation = int(getP("heat"))
	staminaForHeal = getP("stamina")
