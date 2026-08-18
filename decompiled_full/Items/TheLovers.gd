extends Card

onready var heartParticles = $HeartParticles
onready var healAmp: = getP("healamp") / 100.0
onready var dam: = getP("dam")
onready var regen: = int(getP("regen"))

func cardSecondaryEffectActive():
	return chainPosition % 2 == 0

func doRevealEffect():
	if cardSecondaryEffectActive():
		character().addHealingEfficiency(healAmp)
	
	stealLife(dam, getP_m("lifesteal") / 100.0)
	
	if cardSecondaryEffectActive():
		giveRegeneration(regen)
		heartParticles.activate()
	
	activate()
