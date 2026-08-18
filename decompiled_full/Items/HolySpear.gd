extends Weapon

const activationPulse = preload("res://Items/Animations/BookOfLightActivationPulse.tscn")

onready var activationParticles = $ActivationParticles
onready var buffTimer = $BuffTimer
onready var blockRemovalPerSlot: int = getP1()
onready var buffedSpeed = getP3()
onready var manaCost: int = getP2()
onready var light = $Icon / CircleLight

var blockRemoval: int
var cleanses: int

enum SpearState{
	Inactive, 
	Active, 
	Used
}

var spearState: int

func affectsEmpty(color):
	return true

func canAffect(item):
	return item.hasType(Type.Holy)

func onPrepare():
	var numSlots = getNumEmptyAffectedCells() + getNumAffectedItems()
	blockRemoval = blockRemovalPerSlot * numSlots
	cleanses = numSlots
	
	setState(SpearState.Inactive)
	connectForCombat(character(), "character_mana_changed", "checkTrigger")
	connectForCombat(character(), "character_invulnerable_end", "onInvuEnded")

func onPreDealDamage_late(damageRes: DamageResult):
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
		Util.createPulse(activationPulse, self, sockets[0].global_position)
		

func buffEnded():
	setState(SpearState.Used, true)
	reduceSpeed(buffedSpeed / 100.0)

func onCombatEnd():
	buffTimer.stop()
	
func onShopEntered():
	onStateChanged(SpearState.Inactive)

func onStateChanged(_spearState):
	if _spearState == SpearState.Inactive:
		activationParticles.deactivate()
		light.self_modulate = Color.white
		light.show()
	
	elif _spearState == SpearState.Active:
		activationParticles.activate()
		light.self_modulate = Color(1.3, 1.3, 1.3, 1)
		light.show()
	
	else:
		activationParticles.deactivate()
		light.hide()
	
	spearState = _spearState

func getTriggerPriority() -> int:
	return Priority.Normal + 2
