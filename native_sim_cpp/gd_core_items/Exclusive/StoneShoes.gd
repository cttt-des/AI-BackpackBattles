extends Item
var hasActivated: bool
var luck
var empower
var damReduction
var healthThreshold
var buffTimer
var activationParticles

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
		opponent().changeTypedDamageFactor(CoreDamageSource.Type.Ranged, - damReduction)
		opponent().changeEffectDamageFactor( - damReduction)
		consume()


func onBuffTimeout():
	opponent().changeTypedDamageFactor(CoreDamageSource.Type.Ranged, damReduction)
	opponent().changeEffectDamageFactor(damReduction)
	setState(false)


func onCombatEnd():
	buffTimer.stop()


func onShopEntered():
	onStateChanged(false)


func onStateChanged(damResActive):
	if damResActive:
		pass
	else:
		pass


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 3

func _readyInit():
	._readyInit()
	luck = getP("luck")
	empower = getP("empower")
	damReduction = getP("damreduction") / 100.0
	healthThreshold = getP1() / 100.0 - 0.0001
	buffTimer = newItemTimer("BuffTimer", "onBuffTimeout", false)
