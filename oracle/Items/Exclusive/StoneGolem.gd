extends Weapon

const stunParticles = preload("res://Items/Particles/StunParticles.tscn")

onready var empower = getP("empower")
onready var regenThreshold = getP("regen")
onready var bagOfStonesDescriptor = ItemBook.getDescriptor("Bag of Stones")
onready var activationParticles1 = $Icon / ActivationParticles1
onready var activationParticles2 = $Icon / ActivationParticles2

var activated: bool
var hasStunned: bool

func canAffect(item):
	return item.isA(bagOfStonesDescriptor)

func onPrepare():
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")
	setState(false)

func onPreCombatStart():
	addBonusDamage(getP("bonusdam") * getNumAffectedItems())

func onRegenChanged(amount, event):
	if not activated and amount > 0:
		if character().getRegeneration() >= regenThreshold:
			setState(true, true)
			var event2 = useRegeneration(regenThreshold, event)
			giveBlock(getBlock(), true, event2)
			baseCooldownOverride = getP4()
			updateBaseCooldown()

func attack(triggerEvent = null):
	hasStunned = false
	var res: DamageResult = dealDamage(triggerEvent)
	if hasStunned:
		activate(res, true, false, ActivationAni.Tackle)
	else:
		activate(res)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		giveEmpower(empower)

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		if rollChance():
			hasStunned = true
			stun(getP_m("dur_stun"), damageRes.event)
			var particles = ObjectPool.particleOneShot(stunParticles, sprite)
			particles.position = Vector2(100, 0)

func onShopEntered():
	onStateChanged(false)

func onStateChanged(active):
	if active:
		activationParticles1.activate()
		activationParticles2.activate()
	else:
		activationParticles1.deactivate()
		activationParticles2.deactivate()
	
	activated = active

func getTriggerPriority() -> int:
	return Priority.High + 1
