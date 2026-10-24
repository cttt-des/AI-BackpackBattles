extends Food

onready var manaNeeded: = int(getP("manat"))
onready var stamina: = getP("stamina")

func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event2 = useMana(manaNeeded)
		heal(getP_m("heal"), event2)
		giveStamina(stamina, event2)
	activate()

func getTranslatedName(removeLinebreaks = false) -> String:
	if TranslationServer.get_locale() == "en":
		if not Game.itemLibrary.isOpen and Util.flip(0.001):
			var _name = "Manana"
			for i in Util.rng.randi_range(0, 3):
				_name += "na"
			return _name
	
	return .getTranslatedName(removeLinebreaks)
