extends "res://gd_core_items/Exclusive/Phoenix.gd"
var fireMultiplicity

func getTypeMultiplicity(type: int) -> int:
	if type == CoreConst.Type.Fire:
		return fireMultiplicity
	else:
		return .getTypeMultiplicity(type)


func canAffect(item):
	return item.hasType(CoreConst.Type.Fire)


func onPrepare():
	.onPrepare()
	addCritChancePercent(getChance() * getNumAffected_type(CoreConst.Type.Fire))

func _readyInit():
	._readyInit()
	fireMultiplicity = int(getP("fire"))
