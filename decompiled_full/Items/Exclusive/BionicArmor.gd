extends Item

onready var staminaRegenMalus = - getP("staminaregen") / 100.0
onready var healthThreshold = getP("healtht")
onready var maxStamina = getP("maxstamina")
onready var staminaThreshold = getP("staminat1")
onready var staminaUsed = getP("staminat2")
onready var empower = int(getP("empower"))
onready var block2: = int(getP("block"))

var blockHealthAcc: int

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
