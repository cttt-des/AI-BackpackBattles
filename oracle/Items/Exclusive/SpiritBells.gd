extends "res://Items/LeatherHelm.gd"

onready var buffFactor: = getP("buffs") / 100.0

var pets: Dictionary

var boostedCompanions: = 0

func onBought():
	boostedCompanions = 1

func getData():
	return boostedCompanions

func setData(data):
	if data != null:
		boostedCompanions = data

func isAffectingDistinct(color = Affected.Primary) -> bool:
	return color == Affected.Primary

func canAffect(item):
	return item.hasType(Type.Pet)

func getBuffDur() -> float:
	var dur = getP_m("dur_base")
	dur += getP_m("dur_bonus") * getNumDistinctAffectedItems()
	return dur

func doCooldownEffect():
	multiplyBuffsLimit(buffFactor, 1000)
	onAfterEffectFinished()

func onItemRoll(descr):
	if descr in ItemBook.spiritCompanionDescriptors and boostedCompanions > 0:
		ItemBook.multiplyWeight(1.5)

func onItemRolled(descr):
	if descr in ItemBook.spiritCompanionDescriptors:
		boostedCompanions -= 1

func getRelatedItems():
	return ItemBook.spiritCompanionDescriptors
