extends Item
class_name Cube
var affectedItem = null
var cdAdvance
var penaltyFactor

func getDescription(wrapInColor = true) -> String:
	var descr = descriptor.getDescription()
	descr += "\n\n" + ctx.util.tra("Cube_HINT")
	return insertParameters(descr, wrapInColor)


func advanceAffectedItem():
	if not affectedItem in ctx.cube_advanced:
		ctx.cube_advanced[affectedItem] = self
		affectedItem.advanceCooldownSeconds(cdAdvance)
	else:
		affectedItem.advanceCooldownSeconds(cdAdvance * penaltyFactor)
		

func _readyInit():
	._readyInit()
	cdAdvance = getP("cdadvance")
	penaltyFactor = 1.0 - getP("penalty") / 100.0
