extends Item
var deathPrevented = false
var normalSprite
var invuTimer
var lanternLight

func canAffect(item):
	return item.hasType(CoreConst.Type.Fire)


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Dark)


func onPrepare():
	setState(false)
	connectForCombat(character(), "character_damaged", "onDamaged")
	connectForCombat(character(), "reincarnated", "onReincarnate")


func onDamaged(_damage, event):
	if deathPrevented:
		return
	
	if character().getCurrentHealth() <= 0:
		setState(true)
		var duration = getP_m("dur_invu")
		invuTimer.start(duration)
		character().makeInvulnerable(duration, self, event)
		var healAmount = round(getP2() / 100.0 * character().getMaxHealth())
		var event2 = character().reincarnate(healAmount, false, self, event)
		
		activate()
	

func onCombatStart():
	character().loseHealth(getP1() / 100.0 * character().getMaxHealth(), self)
	
	
	activate()


func onReincarnate(event):
	var dam = getMinDamage() * getNumAffected_type(CoreConst.Type.Fire)
	if dam > 0:
		var damageRes = dealEffectDamage(dam, event)
	
	var numDebuffs: int = getP5() * getNumAffectedItems(CoreConst.Affected.Secondary)
	inflictRandomDebuffs(numDebuffs, event)
	
	
	

func invuEnded():
	pass
	


func onCombatEnd():
	invuTimer.stop()
	


func getTriggerPriority() -> int:
	return CoreConst.Priority.High


func onShopEntered():
	onStateChanged(false)


func onStateChanged(_deathPrevented: bool):
	deathPrevented = _deathPrevented
	if deathPrevented:
		pass
	else:
		pass

func _readyInit():
	._readyInit()
	invuTimer = newItemTimer("InvuTimer", "invuEnded", false)
	
	damageSource = CoreDamageSource.new().setItem(self)
	
