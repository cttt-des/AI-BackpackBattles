extends Cube
var hasActivated: bool
var healthThreshold
var healReduction

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	hasActivated = false
	affectedItem = getFirstAffectedItem()
	connectForCombat(opponent(), "character_damaged", "onDamaged")


func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = opponent().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		
		if affectedItem != null:
			advanceAffectedItem()
		
		opponent().reduceHealingEfficiency(healReduction)
		consume()

func _readyInit():
	._readyInit()
	healthThreshold = getP("healtht") / 100.0 - 0.0001
	healReduction = getP("healreduction") / 100.0
