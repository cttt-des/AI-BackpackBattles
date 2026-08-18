extends Card

onready var fireParticles = $Fire
onready var damFactor: = getP("damfactor") / 100.0
onready var heat: = int(getP2())

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)
	
func doRevealEffect():
	character().changeEffectDamageFactor(damFactor)
	var dam = descriptor.minDam + getP1() * chainPosition
	var res = dealEffectDamage(dam)
	giveHeat(heat)
	
	activate(res)
	fireParticles.activate()
