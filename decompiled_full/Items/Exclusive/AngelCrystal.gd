extends Item

onready var regen: = int(getP("regen"))
onready var regenPerHoly: = int(getP("regen_holy"))
onready var empower: = int(getP("empower"))
onready var empowerPerHoly: = int(getP("empower_holy"))

func canAffect(item):
	return item.hasType(Type.Holy)

func onPrepare():
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")

func onCombatStart():
	giveRegeneration(regen + regenPerHoly * getNumAffectedItems())
	activate()

func doCooldownEffect():
	giveEmpower(empower + empowerPerHoly * getNumAffectedItems())
	onAfterEffectFinished()

func onRegenChanged(amount, event):
	if amount > 0:
		giveMaxHealth(getP_m("maxhealth") * amount, event)
		miniActivate()
