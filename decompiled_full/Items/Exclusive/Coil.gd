extends Item

onready var numBuffs: = int(getP("buffs"))
onready var maxActivations: = int(getP("max"))

var numActivations: int

func onPrepare():
	numActivations = 0

func onChargeReceived(_charge):
	if numActivations < maxActivations:
		numActivations += 1
		stealRandomBuff(numBuffs)
		if numActivations == maxActivations:
			consumed = true
		miniActivate()

	
































