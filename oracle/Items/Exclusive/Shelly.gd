extends Item

onready var cleanses: = int(getP("debuffs"))
onready var potionSpeed: = getP("speed") / 100.0

func canAffect(item):
	return item.hasType(Type.Potion)

func doCooldownEffect():
	cleanseRandomDebuffs(cleanses)
	heal()
	activate()

func onPrepare():
	character().changeDebuffProtectionChance( - getChance())
	addSpeed(potionSpeed * getNumAffectedItems())

func getTriggerPriority() -> int:
	return Priority.High
