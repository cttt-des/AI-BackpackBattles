extends Item
var staminaRegen

func onCombatStart():
	giveMaxHealth(round(getP_m("maxhealth") / 100.0 * character().getMaxHealth()))
	character().giveStaminaRegeneration(staminaRegen)
	activate()


func getTriggerPriority() -> int:
	return CoreConst.Priority.Low


func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var string
	if wrapInColor:
		string = ctx.util.tr("TOOLTIP_Always Offered").format(
			{"round": null})
	else:
		string = ctx.util.tr("TOOLTIP_Always Offered").format(
			{"round": descriptor.appearRounds[0]})
	
	descr += "\n\n" + string
	return descr


func getSalesMultiplier():
	return 0.2

func _readyInit():
	._readyInit()
	staminaRegen = getP("stamina") / 100.0
