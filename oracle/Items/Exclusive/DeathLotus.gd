extends Item

onready var mana: = int(getP("mana"))
onready var buffs: = int(getP("buffs"))
onready var darkSpeed: = getP("speed") / 100.0
onready var luckNeeded: = int(getP("luckt"))
onready var stamina: = getP("stamina")

func canAffect(item):
	return item.hasType(Type.Dark)

func onPrepare():
	addSpeed(getNumAffectedItems() * darkSpeed)
	
func doCooldownEffect():
	giveMana(mana)
	removeRandomBuffs(buffs)
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		giveStamina(stamina, event)
	
	activate()
