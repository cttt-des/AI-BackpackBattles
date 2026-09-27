extends Item
var awakenNow: = false
var speed
var buffs
var buffsAmulet
var light1
var light2
var particles1
var particles2

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	setState(false)
	for item in getAffectedItems():
		item.reduceSpeed(speed)


func onCombatStart():
	var m = getP_m("maxhealth_base")
	m += getNumAffectedItems() * getP_m("maxhealth_item")
	m = round(m / 100.0 * character().getMaxHealth())
	giveMaxHealth(m)
	activate()


func trigger():
	awakenNow = true
	.trigger()


func doCooldownEffect():
	if awakenNow:
		setState(true)
		giveAllBuffs(buffs)
		stun(getP_m("dur_stun"))
		awakenNow = false
		onAfterEffectFinished()
	else:
		giveAllBuffs(buffsAmulet)
		stun(getP_m("dur_stun_amulet"))
		activate()


func onShopEntered():
	onStateChanged(false)


func onStateChanged(awakened: bool):
	if awakened:
		pass
	else:
		pass


func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	descr = descr.replace("$s[", "[shake]")
	descr = descr.replace("$s]", "[/shake]")
	return descr
	

func _readyInit():
	._readyInit()
	speed = getP("speed") / 100.0
	buffs = int(getP("buffs"))
	buffsAmulet = int(getP("buffs_amulet"))
