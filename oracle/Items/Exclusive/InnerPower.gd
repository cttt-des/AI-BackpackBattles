extends Item

onready var luck: = int(getP("luck"))
onready var empower: = int(getP("empower"))
onready var healAmpPerLuck: = getP("healamp") / 100.0
onready var speedPerEmpower: = getP("speed") / 100.0
onready var healAmpMax: = getP("max1") / 100.0
onready var speedMax: = getP("max2") / 100.0

var healAmpAcc: float
var speedAcc: float

func canAffect(item):
	return item.hasCooldown() or item.canHealOrLifesteal()

func onCombatStart():
	giveLucky(luck)
	giveEmpower(empower)
	activate()

func onPrepare():
	healAmpAcc = 0
	speedAcc = 0
	connectForCombat(character(), "character_lucky_changed", "onLuckChanged")
	connectForCombat(character(), "character_empower_changed", "onEmpowerChanged")

func onLuckChanged(amount, event):
	var before = min(healAmpAcc, healAmpMax)
	var dif = amount * healAmpPerLuck
	healAmpAcc += dif
	
	var healAmpToGive = min(healAmpAcc, healAmpMax) - before
	if healAmpToGive != 0:
		for item in getAffectedItems():
			item.changeHealAmp(healAmpToGive)
		

func onEmpowerChanged(amount, event):
	var before = min(speedAcc, speedMax)
	var dif = amount * speedPerEmpower
	speedAcc += dif
	
	var speedToGive = min(speedAcc, speedMax) - before
	if speedToGive != 0:
		for item in getAffectedItems():
			item.addSpeed(speedToGive)
		
