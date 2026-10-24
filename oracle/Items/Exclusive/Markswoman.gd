extends Item

onready var rangedBonusDam: = getP("dam") / 100.0
onready var rangedBonusSpeed: = getP("speed") / 100.0
onready var rangedBonusAcc: = getP("acc")

func canAffect(item):
	return item.descriptor.isRangedWeapon()

func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(rangedBonusSpeed)
		if item.canBeEmpowered():
			item.addBonusDamageFactor(rangedBonusDam)
			item.addAccuracy(rangedBonusAcc)
