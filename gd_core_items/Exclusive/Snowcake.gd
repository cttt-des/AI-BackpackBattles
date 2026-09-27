extends Food
var cold
var coldNeeded
var effectDam

func doCooldownEffect():
	inflictCold(cold)
	if opponent().getCold() >= coldNeeded:
		character().changeEffectDamageFactor(effectDam)
		var dam = descriptor.minDam
		var damageRes = dealEffectDamage(dam)
	activate()

func _readyInit():
	._readyInit()
	cold = int(getP("cold"))
	coldNeeded = int(getP("coldt"))
	effectDam = getP("damfactor") / 100.0
	damageSource = CoreDamageSource.new().setItem(self)

