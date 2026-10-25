extends Item
var vampirism
var blindSpeed
var coldSpeed
var dam
var distortion

func onPrepare():
	connectForCombat(opponent(), "character_cold_changed", "onOpponentColdChanged")
	connectForCombat(opponent(), "character_blind_changed", "onOpponentBlindChanged")


func doCooldownEffect():
	giveVampirism(vampirism)
	stealLife(dam, getP_m("lifesteal") / 100.0)
	activate()


func onOpponentColdChanged(amount, event):
	addSpeed(amount * coldSpeed)


func onOpponentBlindChanged(amount, event):
	addSpeed(amount * blindSpeed)


func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)


func drop():
	var res = .drop()
	return res

func _readyInit():
	._readyInit()
	vampirism = int(getP("vampirism"))
	blindSpeed = getP("speed_blind") / 100.0
	coldSpeed = getP("speed_cold") / 100.0
	dam = getP("dam")
	pass

