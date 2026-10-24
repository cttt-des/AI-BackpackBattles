extends "res://Items/Exclusive/Phoenix.gd"

onready var fireMultiplicity: = int(getP("fire"))

func getTypeMultiplicity(type: int) -> int:
	if type == Type.Fire:
		return fireMultiplicity
	else:
		return .getTypeMultiplicity(type)

func canAffect(item):
	return item.hasType(Type.Fire)

func onPrepare():
	.onPrepare()
	addCritChancePercent(getChance() * getNumAffected_type(Type.Fire))
