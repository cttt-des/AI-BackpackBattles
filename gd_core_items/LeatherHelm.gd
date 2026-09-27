extends Item
var buffsActive: = 0
var buffTimer
var activationParticles
var damReduction

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
		pass
	else:
		pass
	

func _readyInit():
	._readyInit()
	buffTimer = newItemTimer("BuffTimer", "buffEnded", true)
	damReduction = getP1()
