extends Item

onready var buffTimer = $BuffTimer
onready var activationParticles = $ActivationParticles
onready var damReduction: = getP1()
var buffsActive: = 0

func getStunProtectChance():
	return getChance()

func onPrepare():
	character().changeCritResistance(getChance())
	character().changeStunResistance(getStunProtectChance())

func onPreCombatStart():
	
	character().changeDamageResistance(damReduction)
	buffsActive += 1
	setState(buffsActive)
	buffTimer.start(getBuffDur())
	







func getBuffDur() -> float:
	return getP_m("dur")

func onCombatStart():
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
	
