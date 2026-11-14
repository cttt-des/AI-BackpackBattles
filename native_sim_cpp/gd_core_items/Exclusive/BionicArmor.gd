extends Item
var blockHealthAcc: int
var staminaRegenMalus
var healthThreshold
var maxStamina
var staminaThreshold
var staminaUsed
var empower
var block2

func onPrepare():
	blockHealthAcc = 0
	var baseStaminaRegen = character().baseStaminaRegen
	character().giveStaminaRegeneration(staminaRegenMalus * baseStaminaRegen)
	
	connectForCombat(character(), "character_healed", "onHealOrBlockChanged")
	connectForCombat(character(), "character_block_changed", "onHealOrBlockChanged")


func onCombatStart():
	giveBlock()
	activate()


func onHealOrBlockChanged(amount, event):
	if amount > 0:
		blockHealthAcc += amount
		var numProccs = int(blockHealthAcc / healthThreshold)
		if numProccs > 0:
			blockHealthAcc -= numProccs * healthThreshold
			giveMaxStaminaTemporary(maxStamina * numProccs)
			miniActivate()


func doCooldownEffect():
	if character().getCurrentStamina() < staminaThreshold:
		giveBlock(block2)
	else:
		useStamina(staminaUsed)
		giveEmpower(empower)
	activate()

func _readyInit():
	._readyInit()
	staminaRegenMalus = - getP("staminaregen") / 100.0
	healthThreshold = getP("healtht")
	maxStamina = getP("maxstamina")
	staminaThreshold = getP("staminat1")
	staminaUsed = getP("staminat2")
	empower = int(getP("empower"))
	block2 = int(getP("block"))
