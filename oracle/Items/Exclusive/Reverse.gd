extends Card

onready var activationParticles = $ActivationParticles

func cardSecondaryEffectActive():
	return deck and deck.countDuplicates(chainPosition) == 0

func doRevealEffect():
	giveReflectStacks(getP("reflect"))
	
	if cardSecondaryEffectActive():
		stealRandomBuff(getP("steal"))
	
	activationParticles.activate()
	activate()

func getCardDescription(descr) -> String:
	if deck:
		var duplicates = deck.countDuplicates(chainPosition)
		var state = StatModified.No
		if duplicates == 0:
			state = StatModified.Positive
		else:
			state = StatModified.Negative
		descr += "\n" + insertParameter(tr("CARD_DUPLICATES"), "num", duplicates, state, false)
	elif placed:
		descr += "\n" + Util.wrapInColor(tr("CARD_HINT"), Util.paramColor)
	
	return descr
