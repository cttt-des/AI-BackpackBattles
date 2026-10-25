extends Goobert
var dam
var vampirism

func onCombatStart():
	giveVampirism(vampirism)
	activate()


func doCooldownEffect():
	stealLife(dam + character().getVampirism(), getP_m("lifesteal") / 100.0)

func _readyInit():
	._readyInit()
	dam = getP("dam")
	vampirism = int(getP("vampirism"))
