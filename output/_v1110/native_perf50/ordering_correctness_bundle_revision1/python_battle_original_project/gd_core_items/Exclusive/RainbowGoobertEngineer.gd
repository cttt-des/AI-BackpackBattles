extends Goobert
var vampirism
var regen
var stamina
var blind
var dambonus

func doCooldownEffect():
	giveBlock()
	heal()
	giveStamina(stamina)
	giveVampirism(vampirism)
	giveRegeneration(regen)
	inflictBlind(blind)
	
	for item in getAffectedItems():
		if item.canBeEmpowered():
			item.addBonusDamage(dambonus)

func _readyInit():
	._readyInit()
	vampirism = int(getP("vampirism"))
	regen = int(getP("regen"))
	stamina = getP("stamina")
	blind = int(getP("blind"))
	dambonus = getP("dambonus")
