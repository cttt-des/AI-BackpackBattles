extends Card
var manaParticles

func doRevealEffect():
	var mana = getP1() * chainPosition
	giveMana(mana)
	removeRandomBuffs(getP2() * chainPosition)
	activate()

func _readyInit():
	._readyInit()
	pass
