extends Item
var selfBuffs
var opponentBuffs
var regen

func canAffect(item):
	return item.canDamage()


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Dark)


func onPrepare():
	var unhealing = getP("unhealing") / 100.0
	unhealing += getNumAffectedItems(CoreConst.Affected.Secondary) * getP("unhealing2") / 100.0
	character().giveUnhealing(unhealing)
	
	connectToCharacterDebuffs("onDebuffsChanged")
	connectToOpponentBuffs("onOpponentBuffsChanged")


func onDebuffsChanged(amount, event):
	if (amount > 0 and 
		event.origin is Item and 
		event.origin.character() == character()):
		
		var regenToGive = 0
		for i in amount:
			if rollChance():
				regenToGive += regen
			
		if regenToGive > 0:
			giveRegeneration(regenToGive, event)


func onOpponentBuffsChanged(amount, event):
	if (amount < 0 and 
		event.origin is Item and 
		event.origin.character() == character()):
		
		for item in getAffectedItems():
			item.addCritChancePercent(getChance2() * - amount)


func doCooldownEffect():
	giveRandomBuffs(selfBuffs)
	giveRandomBuffs(opponentBuffs, null, CoreConst.getBuffs(), opponent())
	activate()


func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

func _readyInit():
	._readyInit()
	selfBuffs = int(getP("buffs"))
	opponentBuffs = int(getP("buffs2"))
	regen = int(getP("regen"))
