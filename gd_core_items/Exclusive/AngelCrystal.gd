extends Item
var regen
var regenPerHoly
var empower
var empowerPerHoly

func canAffect(item):
	return item.hasType(CoreConst.Type.Holy)


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

func _readyInit():
	._readyInit()
	regen = int(getP("regen"))
	regenPerHoly = int(getP("regen_holy"))
	empower = int(getP("empower"))
	empowerPerHoly = int(getP("empower_holy"))
