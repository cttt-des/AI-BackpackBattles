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
	# decomp Items/Exclusive/OwlSpirit.gd:27 Sound.playSound_process(pickupSound, - 12, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

	# decomp Items/Exclusive/OwlSpirit.gd:31 Sound.playSound(dropSound, volume - 18, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	mana = int(getP("mana"))
	fatigueMana = int(getP("fatiguemana"))
