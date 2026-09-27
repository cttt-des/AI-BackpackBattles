extends Item
var activated = false
var staminaReduction
var spikeRemoval
var empowerRemoval
var healthThreshold
var blockPerHealth

func onPrepare():
	activated = false
	
	connectForCombat(character(), "character_damaged", "onDamaged")
	
	for item in inventory.getItems():
		item.changeStaminaFactor(staminaReduction)


func onCombatStart():
	giveBlock()
	activate()


func doCooldownEffect():
	opponent().loseSpikes(spikeRemoval, self)
	opponent().loseEmpower(empowerRemoval, self)
	activate()


func onDamaged(_healthChange, event):
	if activated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		activated = true
		var bl = character().getMissingHealth() * blockPerHealth
		giveBlock(bl, true, event)
		activate()


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 3

func _readyInit():
	._readyInit()
	staminaReduction = getP("staminacost")
	spikeRemoval = getP("spikes")
	empowerRemoval = getP("empower")
	healthThreshold = getP("healtht") / 100.0
	blockPerHealth = getP("blockperhealth") / 100.0
