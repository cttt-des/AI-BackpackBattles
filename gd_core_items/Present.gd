extends Item
var activationParticles

func onCombatStart():
	giveRandomBuffs(getP1())
	activate()













func onShopEntered():
	pass

func getShopPriority() -> int:
	return CoreConst.Priority.Low + 1

func _readyInit():
	._readyInit()
	pass
