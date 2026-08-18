extends Goobert

onready var vampirism: = int(getP("vampirism"))
onready var regen: = int(getP("regen"))
onready var stamina: = getP("stamina")
onready var blind: = int(getP("blind"))
onready var dambonus: = getP("dambonus")

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
