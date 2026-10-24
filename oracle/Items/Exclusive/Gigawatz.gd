extends Item

onready var maxNumSpeedBoosts: = int(getP("max"))
onready var speedBonus: = getP("speed") / 100.0
onready var damageBonus: = getP("damincrease")
onready var blind: = int(getP("blind"))

var numSpeedboosts: int
var curDamageBonus: int

func _ready():
	damageSource = DamageSource.new().setItem(self)

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
	
