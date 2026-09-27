extends Item
var mana
var buffs
var darkSpeed
var luckNeeded
var stamina

func canAffect(item):
	return item.hasType(CoreConst.Type.Dark)


func onPrepare():
	addSpeed(getNumAffectedItems() * darkSpeed)
	

func doCooldownEffect():
	giveMana(mana)
	removeRandomBuffs(buffs)
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		giveStamina(stamina, event)
	
	activate()

func _readyInit():
	._readyInit()
	mana = int(getP("mana"))
	buffs = int(getP("buffs"))
	darkSpeed = getP("speed") / 100.0
	luckNeeded = int(getP("luckt"))
	stamina = getP("stamina")
