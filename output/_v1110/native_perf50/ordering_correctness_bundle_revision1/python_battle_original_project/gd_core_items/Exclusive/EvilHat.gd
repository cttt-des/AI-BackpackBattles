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
	# decomp Items/Exclusive/EvilHat.gd:51 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

	# decomp Items/Exclusive/EvilHat.gd:55 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
func _readyInit():
	._readyInit()
	selfBuffs = int(getP("buffs"))
	opponentBuffs = int(getP("buffs2"))
	regen = int(getP("regen"))
