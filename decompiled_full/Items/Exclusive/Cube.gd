extends Item
class_name Cube

onready var cdAdvance: = getP("cdadvance")
onready var penaltyFactor: = 1.0 - getP("penalty") / 100.0
var affectedItem = null

func getDescription(wrapInColor = true) -> String:
	var descr = descriptor.getDescription()
	descr += "\n\n" + Util.tra("Cube_HINT")
	return insertParameters(descr, wrapInColor)

func advanceAffectedItem():
	if not affectedItem in Game.cubeAdvanced:
		Game.cubeAdvanced[affectedItem] = self
		affectedItem.advanceCooldownSeconds(cdAdvance)
	else:
		affectedItem.advanceCooldownSeconds(cdAdvance * penaltyFactor)
		
