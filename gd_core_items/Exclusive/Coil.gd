extends Item
var numActivations: int
var numBuffs
var maxActivations

func onPrepare():
	numActivations = 0


func onChargeReceived(_charge):
	if numActivations < maxActivations:
		numActivations += 1
		stealRandomBuff(numBuffs)
		if numActivations == maxActivations:
			consumed = true
		miniActivate()

	
































func _readyInit():
	._readyInit()
	numBuffs = int(getP("buffs"))
	maxActivations = int(getP("max"))
