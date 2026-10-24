extends Item

onready var stamina: = getP("stamina")
onready var buffRefund: = getP("refund_buffs") / 100.0
onready var staminaRefund: = getP("refund_stamina") / 100.0
onready var speed: = getP("speed") / 100.0
var usedStacks: Dictionary
var staminaUsed: = 0.0

func canAffect(item):
	return item.isClassItem(Game.Classes_Full.Engineer)

func onPrepare():
	connectToCharacterBuffs("onBuffChanged")
	for buff in Game.getBuffs():
		usedStacks[buff] = 0.0
	
	connectForCombat(character(), "character_used_stamina", "onStaminaUsed")
	staminaUsed = 0
	
	addSpeed(speed * getNumAffectedItems())

func onCombatStart():
	giveMaxStaminaTemporary(stamina, null, false)
	activate()

func onBuffChanged(amount, event):
	if amount < 0 and event.getParam("used", false):
		var used = - amount
		var buffType = event.getType()
		usedStacks[buffType] += used

func onStaminaUsed(amount):
	staminaUsed += amount

func doCooldownEffect():
	
	for buffType in usedStacks:
		var toRefund = int(round(usedStacks[buffType] * buffRefund))
		
		if toRefund > 0:
			usedStacks[buffType] -= toRefund
			giveStacks(character(), buffType, toRefund)
	
	giveStamina(staminaUsed * staminaRefund)
	staminaUsed = 0
	
	activate()
