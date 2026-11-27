extends Item
var activated: = false
var regenNeeded
var numStealedBuffs
var fillAnimation

func canAffect(item):
	return item.hasType(CoreConst.Type.Dark)


func onPrepare():
	setState(false)
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")
	addSpeed(getNumAffectedItems() * getP("darkspeed") / 100.0)
	

func doCooldownEffect():
	stealRandomBuff(numStealedBuffs, null, CoreConst.getBuffs(), CoreConst.EventType.Regeneration)
	activate()


func onRegenChanged(amount, event):
	if amount > 0 and not activated and character().getRegeneration() >= regenNeeded:
		setState(true, true)
		useRegeneration(regenNeeded, event)
		giveMaxHealth(getP_m("maxhealth"), event)
		giveEmpower(getP("empower"), event)
		opponent().reduceHealingEfficiency(getP("healreduction") / 100.0)


func onShopEntered():
	onStateChanged(false)


func getTriggerPriority() -> int:
	return CoreConst.Priority.High


func onStateChanged(filled):
	if activated == filled: return
	activated = filled
	
	if filled:
		pass
	else:
		pass

func _readyInit():
	._readyInit()
	regenNeeded = int(getP("regent"))
	numStealedBuffs = int(getP("buffsteal"))
