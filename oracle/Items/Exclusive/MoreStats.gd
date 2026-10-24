extends Item

onready var damageFactor: = getP("dam") / 100.0

func canAffect_global(item):
	return item.canBeEmpowered()

func onCombatStart():
	for item in inventory.getItems():
		if canAffect_global(item):
			item.addBonusDamageFactor(damageFactor)
	giveMaxHealth(round(getP_m("maxhealth") / 100.0 * character().getMaxHealth()))
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
