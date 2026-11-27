extends Item
var hasActivated: bool
var healthThreshold
var empower
var debuffs
var dodges

func onPrepare():
	hasActivated = false
	connectForCombat(character(), "character_damaged", "onDamaged")


func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		giveEmpower(empower, event)
		cleanseRandomDebuffs(debuffs)
		character().changeDodgeStacks(dodges)
		consume()


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 2

func _readyInit():
	._readyInit()
	healthThreshold = getP("healtht") / 100.0 - 0.0001
	empower = int(getP("empower"))
	debuffs = int(getP("cleanse"))
	dodges = int(getP("dodge"))
