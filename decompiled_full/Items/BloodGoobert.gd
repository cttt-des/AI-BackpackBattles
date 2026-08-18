extends Goobert

onready var dam: = getP("dam")
onready var vampirism: = int(getP("vampirism"))

func onCombatStart():
	giveVampirism(vampirism)
	activate()

func doCooldownEffect():
	stealLife(dam + character().getVampirism(), getP_m("lifesteal") / 100.0)
