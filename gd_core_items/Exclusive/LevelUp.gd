extends Item
var stamina
var mana
var luck
var speedPerRound
var buyRound

func onPrepare():
	var roundsPassed = ctx.cur_round - buyRound
	addSpeed(roundsPassed * speedPerRound)


func doCooldownEffect():
	giveMaxHealth(getP_m("maxhealth"))
	giveStamina(stamina)
	giveMana(mana)
	giveLucky(luck)
	activate()









func _readyInit():
	._readyInit()
	stamina = getP("stamina")
	mana = int(getP("mana"))
	luck = int(getP("luck"))
	speedPerRound = getP("speed") / 100.0
	buyRound = int(getP("skillround"))
