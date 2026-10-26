extends Food
var manaNeeded
var stamina

func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event2 = useMana(manaNeeded)
		heal(getP_m("heal"), event2)
		giveStamina(stamina, event2)
	activate()


func getTranslatedName(removeLinebreaks = false) -> String:
	return ""

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	stamina = getP("stamina")
