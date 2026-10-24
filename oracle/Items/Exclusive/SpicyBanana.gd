extends Item

onready var bananaDescriptor = ItemBook.getDescriptor("Banana")
onready var manananaDescriptor = ItemBook.getDescriptor("Mananana")
onready var heatPerActivation: = int(getP("heat"))
onready var staminaForHeal: = getP("stamina")
var staminaUsed: float
var boostedBananas: = 0

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
	if descr == bananaDescriptor and boostedBananas > 0:
		ItemBook.multiplyWeight(1.5)

func onItemRolled(descr):
	if descr == bananaDescriptor:
		boostedBananas -= 1
