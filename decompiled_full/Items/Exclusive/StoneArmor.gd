extends Item

onready var staminaReduction = getP("staminacost")
onready var spikeRemoval = getP("spikes")
onready var empowerRemoval = getP("empower")
onready var healthThreshold = getP("healtht") / 100.0
onready var blockPerHealth = getP("blockperhealth") / 100.0

var activated = false

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
	return Priority.High + 3
