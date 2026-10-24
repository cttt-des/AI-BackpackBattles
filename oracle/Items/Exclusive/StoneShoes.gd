extends Item

onready var luck: = getP("luck")
onready var empower: = getP("empower")
onready var damReduction: = getP("damreduction") / 100.0
onready var healthThreshold: = getP1() / 100.0 - 0.0001
onready var buffTimer: = $BuffTimer
onready var activationParticles = $ActivationParticles

var hasActivated: bool

func onPrepare():
	setState(false)
	hasActivated = false
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		giveLucky(getP2(), event)
		giveEmpower(getP3(), event)
		giveBlock(getBlock(), true, event)
		buffTimer.start(getP_m("dur"))
		setState(true)
		opponent().changeTypedDamageFactor(DamageSource.Type.Ranged, - damReduction)
		opponent().changeEffectDamageFactor( - damReduction)
		consume()

func onBuffTimeout():
	opponent().changeTypedDamageFactor(DamageSource.Type.Ranged, damReduction)
	opponent().changeEffectDamageFactor(damReduction)
	setState(false)

func onCombatEnd():
	buffTimer.stop()

func onShopEntered():
	onStateChanged(false)

func onStateChanged(damResActive):
	if damResActive:
		activationParticles.activate()
	else:
		activationParticles.deactivate()

func getTriggerPriority() -> int:
	return Priority.High + 3
