extends Item
var staminaRegenPerBuff
var numBuffs: int

func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


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

func _readyInit():
	._readyInit()
	numBuffs = getP2()
