extends Item
var rangedBonusDam
var rangedBonusSpeed
var rangedBonusAcc

func canAffect(item):
	return item.descriptor.isRangedWeapon()


func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(rangedBonusSpeed)
		if item.canBeEmpowered():
			item.addBonusDamageFactor(rangedBonusDam)
			item.addAccuracy(rangedBonusAcc)

func _readyInit():
	._readyInit()
	rangedBonusDam = getP("dam") / 100.0
	rangedBonusSpeed = getP("speed") / 100.0
	rangedBonusAcc = getP("acc")
