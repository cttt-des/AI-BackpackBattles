extends Card

onready var manaParticles = $ManaParticles

func doRevealEffect():
	var mana = getP1() * chainPosition
	giveMana(mana)
	removeRandomBuffs(getP2() * chainPosition)
	activate()
	manaParticles.activate()
