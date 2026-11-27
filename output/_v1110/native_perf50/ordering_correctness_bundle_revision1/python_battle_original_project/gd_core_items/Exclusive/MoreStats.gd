extends Item
var damageFactor

func canAffect_global(item):
	return item.canBeEmpowered()


func onCombatStart():
	for item in inventory.getItems():
		if canAffect_global(item):
			item.addBonusDamageFactor(damageFactor)
	giveMaxHealth(round(getP_m("maxhealth") / 100.0 * character().getMaxHealth()))
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
	damageFactor = getP("dam") / 100.0
