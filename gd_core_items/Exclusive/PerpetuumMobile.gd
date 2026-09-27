extends Item
var usedStacks: Dictionary
var staminaUsed: = 0.0
var stamina
var buffRefund
var staminaRefund
var speed

func canAffect(item):
	return item.isClassItem(CoreConst.Classes_Full.Engineer)


func onPrepare():
	connectToCharacterBuffs("onBuffChanged")
	for buff in CoreConst.getBuffs():
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

func _readyInit():
	._readyInit()
	stamina = getP("stamina")
	buffRefund = getP("refund_buffs") / 100.0
	staminaRefund = getP("refund_stamina") / 100.0
	speed = getP("speed") / 100.0
