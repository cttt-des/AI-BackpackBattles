extends Item

onready var buffTimer = $BuffTimer
onready var activationParticles = $ActivationParticles
onready var damReduction: = getP1()
var nullifyApplied: bool
var buffsActive: = 0

func onPrepare():
	opponent().reduceHealingEfficiency(getP3() / 100.0)
	nullifyApplied = false

func onPreCombatStart():
	character().changeDamageResistance(damReduction)

func onCombatStart():
	if not nullifyApplied:
		nullifyApplied = true
		opponent().changeBuffNullifyChances(getChance())
	
	buffTimer.start(getP_m("dur"))
	buffsActive += 1
	setState(buffsActive)
	activate()

func buffEnded():
	character().changeDamageResistance( - damReduction)
	buffsActive -= 1
	setState(buffsActive)

func onCombatEnd():
	buffTimer.stop()

func onShopEntered():
	buffsActive = 0
	onStateChanged(buffsActive)

func onStateChanged(_buffsActive):
	if _buffsActive > 0:
		activationParticles.activate()
	else:
		activationParticles.deactivate()
