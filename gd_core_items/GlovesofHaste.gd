extends Item
var bonusSpeed

func canAffect(item):
	return item.hasCooldown()
	

func onCombatStart():
	for item in getAffectedItems():
		item.addSpeed(bonusSpeed)
	activate()

func _readyInit():
	._readyInit()
	bonusSpeed = getP1() / 100
