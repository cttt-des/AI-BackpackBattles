extends Weapon
var hasActivated: bool
var manaNeeded
var blind
var numDebuffs
var dmgReductionTimer
var healthThreshold
var bonusSpeed
var damReduction

func canAffect(item):
	return item.hasCooldown() or item.gainsStack(CoreConst.Stack.Mana)


func onPrepare():
	updateShaderRotation()
	hasActivated = false
	connectForCombat(character(), "character_damaged", "onDamaged")


func onDealtDamage(damageRes: CoreDamageResult):
	if (damageRes.hasHit() and 
		character().getMana() >= manaNeeded):
		
		var event = useMana(manaNeeded, damageRes.event)
		var duration = getP_m("dur_blind")
		giveStacksTemporary(opponent(), CoreConst.EventType.Blind, 
			blind, duration, event)
		
		if rollChance():
			stun(getP_m("dur_stun"), event)
		
		cleanseRandomDebuffs(numDebuffs, event)


func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		
		for item in getAffectedItems():
			item.addSpeed(bonusSpeed)
			item.changeAmplificiationChancePercent(CoreConst.EventType.Mana, getChance2())
		
		dmgReductionTimer.start(getP_m("dur_dmgreduction"))
		character().changeDamageResistance(damReduction)
		
		giveBlock(getBlock(), true, event)
		


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 2


func onDmgReductionTimerTimeout():
	character().changeDamageResistance( - damReduction)


func onCombatEnd():
	dmgReductionTimer.stop()


func showCooldown(progress: float):

	progress = rotateProgress(progress * 1.0 + 0.05)


func clearSpriteMaterial():
	pass


func giveProgressMaterial():
	pass


func updateShaderRotation():
	.updateShaderRotation()

func getTextureSize() -> Vector2:
	return Vector2.ZERO

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	blind = int(getP("blind"))
	numDebuffs = int(getP("cleanse"))
	dmgReductionTimer = newItemTimer("DmgReductionTimer", "onDmgReductionTimerTimeout", false)
	healthThreshold = getP("healtht") / 100.0 - 0.0001
	bonusSpeed = getP("speed") / 100.0
	damReduction = getP("dmgreduction")
	pass

