extends Card
var activationParticles

func cardSecondaryEffectActive():
	return deck and deck.countDuplicates(chainPosition) == 0


func doRevealEffect():
	giveReflectStacks(getP("reflect"))
	
	if cardSecondaryEffectActive():
		stealRandomBuff(getP("steal"))
	
	activate()


func getCardDescription(descr) -> String:
	if deck:
		var duplicates = deck.countDuplicates(chainPosition)
		var state = CoreConst.StatModified.No
		if duplicates == 0:
			state = CoreConst.StatModified.Positive
		else:
			state = CoreConst.StatModified.Negative
		descr += "\n" + insertParameter(tr("CARD_DUPLICATES"), "num", duplicates, state, false)
	elif placed:
		descr += "\n" + ctx.util.wrapInColor(tr("CARD_HINT"), ctx.util.paramColor)
	
	return descr

func _readyInit():
	._readyInit()
	pass
