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
	# decomp Items/Exclusive/CatSpirit.gd:27 Sound.playSound_process(pickupSound, - 12, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

	# decomp Items/Exclusive/CatSpirit.gd:31 Sound.playSound(dropSound, volume - 18, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	luck = int(getP("luck"))
	empower = int(getP("empower"))
