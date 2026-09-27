extends Item
var numSpeedboosts: int
var curDamageBonus: int
var maxNumSpeedBoosts
var speedBonus
var damageBonus
var blind

func onPrepare():
	curDamageBonus = 0
	numSpeedboosts = 0


func onChargeReceived(_charge):
	if numSpeedboosts < maxNumSpeedBoosts:
		addSpeed(speedBonus)
		numSpeedboosts += 1


func doCooldownEffect():
	inflictBlind(blind)
	var dam = descriptor.minDam + curDamageBonus
	var res = dealEffectDamage(dam)
	activate()
	curDamageBonus += damageBonus
	

func _readyInit():
	._readyInit()
	maxNumSpeedBoosts = int(getP("max"))
	speedBonus = getP("speed") / 100.0
	damageBonus = getP("damincrease")
	blind = int(getP("blind"))
	damageSource = CoreDamageSource.new().setItem(self)

