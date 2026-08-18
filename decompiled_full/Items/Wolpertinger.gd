extends Item

var staminaRegenPerBuff
onready var numBuffs: int = getP2()

func canAffect(item):
	return item.hasType(Type.Pet)

func onPrepare():
	addSpeed(getNumAffectedItems() * getP3() / 100.0)
	connectToCharacterBuffs("onBuffChanged")
	var baseStaminaRegen = character().baseStaminaRegen
	staminaRegenPerBuff = getP1() * baseStaminaRegen / 100.0
	
func doCooldownEffect():
	giveLeastBuffs(numBuffs)
	activate()

func onBuffChanged(amount, event):
	
	character().giveStaminaRegeneration(amount * staminaRegenPerBuff)

