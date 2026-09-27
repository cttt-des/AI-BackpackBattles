extends SpiritCompanion
var manaNeeded
var luck
var empower

func canAffect(item):
	return item.canDamage()


func onPrepare():
	for item in getAffectedItems():
		item.addCritChancePercent(getChance())


func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveLucky(luck, event)
		giveEmpower(empower, event)
	
	activate()



func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	luck = int(getP("luck"))
	empower = int(getP("empower"))
