extends Item

onready var stamina: = getP("stamina")
onready var mana: = int(getP("mana"))
onready var luck: = int(getP("luck"))
onready var speedPerRound: = getP("speed") / 100.0
onready var buyRound: = int(getP("skillround"))

func onPrepare():
	var roundsPassed = Game.curRound - buyRound
	addSpeed(roundsPassed * speedPerRound)

func doCooldownEffect():
	giveMaxHealth(getP_m("maxhealth"))
	giveStamina(stamina)
	giveMana(mana)
	giveLucky(luck)
	activate()









