extends SpiritCompanion
var manaNeeded
var mana
var fatigueMana

func canAffect(item):
	return item.gainsBuffs()


func onPrepare():
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())
	

func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		if ctx.combat.hasFatigueStarted():
			giveMana(fatigueMana, event)
		else:
			giveMana(mana, event)
	activate()


func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	mana = int(getP("mana"))
	fatigueMana = int(getP("fatiguemana"))
