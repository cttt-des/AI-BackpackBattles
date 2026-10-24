extends Item



onready var light = $Icon / Light
onready var blindAmount: = int(getP("blind"))
onready var speedBonus: = getP("speed") / 100.0

func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)
	light.show()
	

func drop():
	var res = .drop()
	light.hide()
	return res

func canAffect(item):
	return item.hasCooldown()

func onPrepare():
	setState(false)

func doCooldownEffect():
	var duration = getP_m("dur_blind")
	giveStacksTemporary(opponent(), Game.EventType.Blind, 
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
		light.show()
	else:
		light.hide()
