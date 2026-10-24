extends Item

onready var vampirism: = int(getP("vampirism"))
onready var blindSpeed: = getP("speed_blind") / 100.0
onready var coldSpeed: = getP("speed_cold") / 100.0
onready var dam: = getP("dam")
onready var distortion = $Icon / Distortion

func _ready():
	distortion.hide()

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
	distortion.show()

func drop():
	var res = .drop()
	distortion.hide()
	return res
