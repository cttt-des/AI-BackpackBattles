extends Weapon
var activated: bool
var hasStunned: bool
var empower
var regenThreshold
var bagOfStonesDescriptor
var activationParticles1
var activationParticles2

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
	var res: CoreDamageResult = dealDamage(triggerEvent)
	if hasStunned:
		activate(res, true, false, ActivationAni.Tackle)
	else:
		activate(res)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		giveEmpower(empower)


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if rollChance():
			hasStunned = true
			stun(getP_m("dur_stun"), damageRes.event)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(active):
	if active:
		pass
	else:
		pass
	
	activated = active


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 1

func _readyInit():
	._readyInit()
	empower = getP("empower")
	regenThreshold = getP("regen")
	bagOfStonesDescriptor = ctx.item_book.getDescriptor("Bag of Stones")
