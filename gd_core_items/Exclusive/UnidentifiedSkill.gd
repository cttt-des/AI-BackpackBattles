extends Item
var skillPool

func getSkillPool():
	pass

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		var skill = skillPool.pick_random()
		call_deferred("identifySkill", dropRes, skill)


func identifySkill(dropResult, skillDescriptor):
	pass

func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var string
	if wrapInColor:
		string = ctx.util.tr("TOOLTIP_Always Offered2").format(
			{"round1": null, 
				"round2": null})
	else:
		string = ctx.util.tr("TOOLTIP_Always Offered2").format(
			{"round1": descriptor.appearRounds[0], 
				"round2": descriptor.appearRounds[1]})
	descr += "\n\n" + string
	return descr


func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 6


func getRelatedItemHeight() -> int:
	return 80

func _readyInit():
	._readyInit()
	connect("dropped", self, "onDropped")
	if ownerType == CoreConst.Owner.Shop:
		call_deferred("getSkillPool")

