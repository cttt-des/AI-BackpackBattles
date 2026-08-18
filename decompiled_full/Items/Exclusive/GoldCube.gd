extends Cube

onready var healthThreshold: = getP("healtht") / 100.0 - 0.0001
var hasActivated: bool

func canAffect(item):
	return item.hasCooldown()

func onPrepare():
	hasActivated = false
	affectedItem = getFirstAffectedItem()
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		
		if affectedItem != null:
			advanceAffectedItem()
		
		heal(getP_m("heal") + getP_m("heal_regen") * character().getRegeneration())
		consume()
