extends Item

onready var speed: = getP("speed") / 100.0
onready var buffs: = int(getP("buffs"))
onready var buffsAmulet: = int(getP("buffs_amulet"))
onready var light1 = $Icon / Light1
onready var light2 = $Icon / Light2
onready var particles1 = $Icon / Particles1
onready var particles2 = $Icon / Particles2

var awakenNow: = false

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
		light1.show()
		light2.show()
		particles1.activate()
		particles2.activate()
	else:
		light1.hide()
		light2.hide()
		particles1.deactivate()
		particles2.deactivate()

func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	descr = descr.replace("$s[", "[shake]")
	descr = descr.replace("$s]", "[/shake]")
	return descr
	
