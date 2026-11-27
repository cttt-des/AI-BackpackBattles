extends Item
var light
var blindAmount
var speedBonus

func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)
	


func drop():
	var res = .drop()
	return res


func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	setState(false)


func doCooldownEffect():
	var duration = getP_m("dur_blind")
	giveStacksTemporary(opponent(), CoreConst.EventType.Blind, 
		blindAmount, duration)
	
	onAfterEffectFinished()


func onChargeReceived(_charge):
	if numCharges == 1:
		setState(true)
		for item in getAffectedItems():
			item.addSpeed(speedBonus)


func onChargeLeft(_charge):
	if numCharges == 0:
		setState(false)
		for item in getAffectedItems():
			item.reduceSpeed(speedBonus)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(charged):
	if charged:
		pass
	else:
		pass

func _readyInit():
	._readyInit()
	blindAmount = int(getP("blind"))
	speedBonus = getP("speed") / 100.0
