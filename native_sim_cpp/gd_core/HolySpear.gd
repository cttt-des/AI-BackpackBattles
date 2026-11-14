extends Weapon
var blockRemoval: int
var cleanses: int
enum SpearState{
	Inactive, 
	Active, 
	Used
}
var spearState: int
var activationParticles
var buffTimer
var blockRemovalPerSlot: int
var buffedSpeed
var manaCost: int
var light

func affectsEmpty(color):
	return true


func canAffect(item):
	return item.hasType(CoreConst.Type.Holy)


func onPrepare():
	var numSlots = getNumEmptyAffectedCells() + getNumAffectedItems()
	blockRemoval = blockRemovalPerSlot * numSlots
	cleanses = numSlots
	
	setState(SpearState.Inactive)
	connectForCombat(character(), "character_mana_changed", "checkTrigger")
	connectForCombat(character(), "character_invulnerable_end", "onInvuEnded")


func onPreDealDamage_late(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		removeBlock(blockRemoval)
		cleanseRandomDebuffs(cleanses)


func onInvuEnded(triggerEvent):
	checkTrigger(0, triggerEvent)


func checkTrigger(_amount, triggerEvent):
	if (spearState == SpearState.Inactive and 
		character().isVulnerable() and 
		checkMana(manaCost)):
		
		setState(SpearState.Active, true)
		var invuDur = getP_m("dur_invu")
		character().makeInvulnerable(invuDur, self, triggerEvent)
		buffTimer.start(invuDur)
		useMana(manaCost, triggerEvent)
		addSpeed(buffedSpeed / 100.0)
		


func buffEnded():
	setState(SpearState.Used, true)
	reduceSpeed(buffedSpeed / 100.0)


func onCombatEnd():
	buffTimer.stop()
	

func onShopEntered():
	onStateChanged(SpearState.Inactive)


func onStateChanged(_spearState):
	if _spearState == SpearState.Inactive:
		pass
	
	elif _spearState == SpearState.Active:
		pass
	
	else:
		pass
	
	spearState = _spearState


func getTriggerPriority() -> int:
	return CoreConst.Priority.Normal + 2

func _readyInit():
	._readyInit()
	buffTimer = newItemTimer("BuffTimer", "buffEnded", false)
	blockRemovalPerSlot = getP1()
	buffedSpeed = getP3()
	manaCost = getP2()
