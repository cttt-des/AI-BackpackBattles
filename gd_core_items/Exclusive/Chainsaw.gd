extends Weapon
const sawSpeed: = 8.0
var sawFrame = 0
var sawTween: SceneTreeTween
var removeBuffs
var slowdown
var sawAnimation

func onPrepare():
	setState(false)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if numCharges > 0:
			stealBuffsFraction(removeBuffs, 1000)
		else:
			removeBuffsFraction(removeBuffs, 1000)
		
		reduceSpeed(slowdown)


func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)


func drop():
	var res = .drop()
	
	return res


func setSawTexture():
	sawFrame += 1
	sawFrame %= 4
	updateShadowTexture()


func onChargeReceived(_charge):
	if numCharges == 1:
		setState(true)
		playPickupSound()


func onChargeLeft(_charge):
	if numCharges == 0:
		setState(false)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(charged):
	if charged:
		pass
	else:
		pass


func playPickupSound():
	pass

func _readyInit():
	._readyInit()
	removeBuffs = getP("buffs") / 100.0
	slowdown = getP("slow") / 100.0
