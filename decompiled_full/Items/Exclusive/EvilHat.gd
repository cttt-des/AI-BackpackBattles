extends Item

const pickupSound = preload("res://Assets/Sound/Hat1.ogg")
const dropSound = preload("res://Assets/Sound/Hat2.ogg")

onready var selfBuffs: = int(getP("buffs"))
onready var opponentBuffs: = int(getP("buffs2"))
onready var regen: = int(getP("regen"))

func canAffect(item):
	return item.canDamage()

func canAffect_secondary(item):
	return item.hasType(Type.Dark)

func onPrepare():
	var unhealing = getP("unhealing") / 100.0
	unhealing += getNumAffectedItems(Affected.Secondary) * getP("unhealing2") / 100.0
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
	giveRandomBuffs(opponentBuffs, null, Game.getBuffs(), opponent())
	activate()

func playPickupSound():
	Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))
