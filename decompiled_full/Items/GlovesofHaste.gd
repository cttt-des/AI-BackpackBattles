extends Item

onready var bonusSpeed: = getP1() / 100

func canAffect(item):
	return item.hasCooldown()
	
func onCombatStart():
	for item in getAffectedItems():
		item.addSpeed(bonusSpeed)
	activate()
