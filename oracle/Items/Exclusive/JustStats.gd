extends Item

onready var staminaRegen: = getP("stamina") / 100.0

func onCombatStart():
	giveMaxHealth(round(getP_m("maxhealth") / 100.0 * character().getMaxHealth()))
	character().giveStaminaRegeneration(staminaRegen)
	activate()

func getTriggerPriority() -> int:
	return Priority.Low

func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var string
	if wrapInColor:
		string = Util.tr("TOOLTIP_Always Offered").format(
			{"round": Util.highlight(descriptor.appearRounds[0])})
	else:
		string = Util.tr("TOOLTIP_Always Offered").format(
			{"round": descriptor.appearRounds[0]})
	
	descr += "\n\n" + string
	return descr

func getSalesMultiplier():
	return 0.2
