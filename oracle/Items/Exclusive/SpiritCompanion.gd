extends Item
class_name SpiritCompanion

func getDescription(wrapInColor = true) -> String:
	var descr = descriptor.getDescription()
	
	descr += "\n\n" + Util.tra("Spirit Companion_DESCR")
	return insertParameters(descr, wrapInColor)
