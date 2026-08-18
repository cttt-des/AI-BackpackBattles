extends Food

onready var cold: = int(getP("cold"))
onready var coldNeeded: = int(getP("coldt"))
onready var effectDam: = getP("damfactor") / 100.0

func _ready():
	damageSource = DamageSource.new().setItem(self)

func doCooldownEffect():
	inflictCold(cold)
	if opponent().getCold() >= coldNeeded:
		character().changeEffectDamageFactor(effectDam)
		var dam = descriptor.minDam
		var damageRes = dealEffectDamage(dam)
	activate()

