extends Weapon
var manaUsed: int
var activeEffects: = 0
var coldParticles
var distortion
var manaOnHit
var bonusManaOnHit
var iceSpeed
var bonusDam
var coldOnHit
var manaNeeded1
var manaNeeded2
var manaNeeded3

func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Ice)


func onPrepare():
	connectForCombat(character(), "character_mana_changed", "onManaChanged")
	manaUsed = 0
	addSpeed(iceSpeed * getNumAffectedItems(CoreConst.Affected.Secondary))
	activeEffects = 0
	setState(activeEffects)


func onManaChanged(amount, event):
	if (amount < 0 and 
		event.type == CoreConst.EventType.Mana and 
		event.getParam("used", false)):
		
		manaUsed += abs(amount)
		
		var before = activeEffects
		
		if activeEffects == 0 and manaUsed >= manaNeeded1:
			activeEffects = 1
		
		if activeEffects == 1 and manaUsed >= manaNeeded2:
			activeEffects = 2
			addBonusDamage(bonusDam)
		
		if activeEffects == 2 and manaUsed >= manaNeeded3:
			activeEffects = 3
		
		if before != activeEffects:
			setState(activeEffects)


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		var mana = manaOnHit
		var chance = getChance() * getNumAffectedItems()
		if rollChance(chance):
			mana += bonusManaOnHit
		giveMana(mana, damageRes.event)
		
		if activeEffects >= 1:
			heal(getP_m("heal"), damageRes.event)
		if activeEffects == 3:
			inflictCold(coldOnHit, damageRes.event)


func onShopEntered():
	onStateChanged(0)


func onStateChanged(_activeEffects: int):
	activeEffects = _activeEffects
	if activeEffects == 3:
		pass
	else:
		pass



func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var colors = [ctx.util.triggerColor, ctx.util.triggerColor, ctx.util.triggerColor]
	
	if placed:
		for i in activeEffects:
			colors[i] = ctx.util.modifiedColor
	
	descr = getModeDescription(descr, colors, false, wrapInColor)
	return descr


func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

func _readyInit():
	._readyInit()
	manaOnHit = int(getP("mana"))
	bonusManaOnHit = int(getP("mana2"))
	iceSpeed = getP("speed") / 100.0
	bonusDam = getP("dam")
	coldOnHit = int(getP("cold"))
	manaNeeded1 = int(getP("manat1"))
	manaNeeded2 = int(getP("manat2"))
	manaNeeded3 = int(getP("manat3"))
	if ownerType == CoreConst.Owner.GridStorage:
		pass
	else:
		pass

