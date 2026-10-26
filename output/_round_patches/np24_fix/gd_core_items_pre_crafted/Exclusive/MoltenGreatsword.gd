extends "res://gd_core_items/Greatsword.gd"
var fireMultiplicity
var heatNeeded
var empower

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if character().getHeat() >= heatNeeded:
			var event = useHeat(heatNeeded)
			giveEmpower(empower, event)





func getTypeMultiplicity(type: int) -> int:
	if type == CoreConst.Type.Fire:
		return fireMultiplicity
	else:
		return .getTypeMultiplicity(type)

func _readyInit():
	._readyInit()
	fireMultiplicity = int(getP("fire"))
	heatNeeded = int(getP("heat"))
	empower = int(getP("empower"))
