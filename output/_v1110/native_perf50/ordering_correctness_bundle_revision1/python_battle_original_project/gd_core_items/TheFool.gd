extends Card
var activationParticles

func cardSecondaryEffectActive():
	return chainPosition == 0


func doRevealEffect():
	var bonusSpeed = getP("revealspeed") / 100.0
	for card in deck.cards:
		card.addSpeed(bonusSpeed)
	
	if cardSecondaryEffectActive():
		giveEmpower(getP("empower"))
	
	activate()
	

func _readyInit():
	._readyInit()
	pass
