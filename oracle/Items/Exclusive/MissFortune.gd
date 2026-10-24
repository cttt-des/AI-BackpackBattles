extends Item

onready var luckNeeded = getP("luck")
onready var numBuffs = getP("buffs")
onready var activationParticles = $ActivationParticles

func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		giveMostBuffs(numBuffs, event)
		activationParticles.activate()
	
	activate()
		
