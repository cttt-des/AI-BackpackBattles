extends "res://gd_core_items/LeatherHelm.gd"
var pets: Dictionary
var boostedCompanions: = 0
var buffFactor

func onBought():
	boostedCompanions = 1


func getData():
	return boostedCompanions


func setData(data):
	if data != null:
		boostedCompanions = data


func isAffectingDistinct(color = CoreConst.Affected.Primary) -> bool:
	return color == CoreConst.Affected.Primary


func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


func getBuffDur() -> float:
	var dur = getP_m("dur_base")
	dur += getP_m("dur_bonus") * getNumDistinctAffectedItems()
	return dur


func doCooldownEffect():
	multiplyBuffsLimit(buffFactor, 1000)
	onAfterEffectFinished()


func onItemRoll(descr):
	pass

func onItemRolled(descr):
	pass

func getRelatedItems():
	pass

func _readyInit():
	._readyInit()
	buffFactor = getP("buffs") / 100.0
