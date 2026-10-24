extends Item

const plushies = ["Mrs Struggles", "Miss Fortune"]

onready var speedbuffTimer = $SpeedbuffTimer
onready var activationParticles = $ActivationParticles
onready var healthThreshold: = getP2() / 100.0 - 0.0001
onready var bonusSpeed: = getP3() / 100.0
onready var fatigueDam: = int(getP1())
onready var speedBuffParticles1 = $Icon / ActivationParticles1
onready var speedBuffParticles2 = $Icon / ActivationParticles2

var hasActivated: bool

func canAffect(item):
	return item.hasCooldown()

func onPrepare():
	for debuff in Game.getDebuffs():
		connectForCombat(character(), character().buffs[debuff].signalName, 
		"onDebuffed")
	
	
	hasActivated = false
	setState(false)
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		setState(true)
		for item in getAffectedItems():
			item.addSpeed(bonusSpeed)
		speedbuffTimer.start(getP_m("dur_speed"))
		speedBuffParticles1.activate()
		speedBuffParticles2.activate()
	
func onSpeedbuffTimeout():
	setState(false)
	for item in getAffectedItems():
		item.reduceSpeed(bonusSpeed)

func onDebuffed(amount, event):
	if checkTriggerCount(10):
		if rollChance():
			var debuffType = event.type
			var dur = event.getParam("duration", - 1)
			giveStacksTemporary(opponent(), debuffType, amount, dur, event)
				

func doCooldownEffect():
	inflictFatigueDamage(fatigueDam)
	activationParticles.activate()
	activate()





func onCombatEnd():
	speedbuffTimer.stop()

func getTriggerPriority() -> int:
	return Priority.High + 3

func getDescription(wrapInColor = true) -> String:
	var descr = descriptor.getDescription()
	if Game.showExclusiveContent():
		descr += "\n\n" + Util.tra("Mr Struggles_Plushies")
	return insertParameters(descr, wrapInColor)

func rollShopChance(shopChance = descriptor.shopChance) -> bool:
	if Game.showExclusiveContent():
		return .rollShopChance(shopChance)
	else:
		return false

func getGatedDescriptor(rarity) -> ItemDescriptor:
	return ItemBook.getDescriptor(Util.pickRandomElement(plushies))

func onShopEntered():
	onStateChanged(false)

func onStateChanged(speedBuffActive):
	if speedBuffActive:
		speedBuffParticles1.activate()
		speedBuffParticles2.activate()
	else:
		speedBuffParticles1.deactivate()
		speedBuffParticles2.deactivate()
	
