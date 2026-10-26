extends Card
var fireParticles
var damFactor
var heat

func doRevealEffect():
	character().changeEffectDamageFactor(damFactor)
	var dam = descriptor.minDam + getP1() * chainPosition
	var res = dealEffectDamage(dam)
	giveHeat(heat)
	
	activate(res)

func _readyInit():
	._readyInit()
	damFactor = getP("damfactor") / 100.0
	heat = int(getP2())
	damageSource = CoreDamageSource.new().setItem(self)
	
