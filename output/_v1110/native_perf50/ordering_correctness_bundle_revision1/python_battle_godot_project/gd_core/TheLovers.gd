extends Card
var heartParticles
var healAmp
var dam
var regen

func cardSecondaryEffectActive():
	return chainPosition % 2 == 0


func doRevealEffect():
	if cardSecondaryEffectActive():
		character().addHealingEfficiency(healAmp)
	
	stealLife(dam, getP_m("lifesteal") / 100.0)
	
	if cardSecondaryEffectActive():
		giveRegeneration(regen)
	
	activate()

func _readyInit():
	._readyInit()
	healAmp = getP("healamp") / 100.0
	dam = getP("dam")
	regen = int(getP("regen"))
