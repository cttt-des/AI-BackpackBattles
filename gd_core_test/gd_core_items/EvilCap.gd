extends Item
var nullifyApplied: bool
var buffsActive: = 0
var buffTimer
var activationParticles
var damReduction

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
		pass
	else:
		pass

func _readyInit():
	._readyInit()
	buffTimer = newItemTimer("BuffTimer", "buffEnded", true)
	damReduction = getP1()
