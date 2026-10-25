extends Item
var cleanses
var potionSpeed

func canAffect(item):
	return item.hasType(CoreConst.Type.Potion)


func doCooldownEffect():
	cleanseRandomDebuffs(cleanses)
	heal()
	activate()


func onPrepare():
	character().changeDebuffProtectionChance( - getChance())
	addSpeed(potionSpeed * getNumAffectedItems())


func getTriggerPriority() -> int:
	return CoreConst.Priority.High

func _readyInit():
	._readyInit()
	cleanses = int(getP("debuffs"))
	potionSpeed = getP("speed") / 100.0
