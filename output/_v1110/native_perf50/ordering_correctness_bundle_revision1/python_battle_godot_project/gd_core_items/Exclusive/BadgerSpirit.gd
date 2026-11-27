extends SpiritCompanion
var activated: bool
var healthThreshold
var manaNeeded

func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


func onPrepare():
	activated = false
	connectForCombat(character(), "character_damaged", "onDamaged")


func onDamaged(_healthChange, event):
	if not activated and character().getRelativeHealth() < healthThreshold:
		activated = true
		heal(character().getMaxHealth() * getP_m("heal") / 100.0, event)


func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveMaxHealth(getP_m("maxhealth") + getNumAffectedItems() * 
			getP_m("maxhealth_bonus"), event)
	activate()


func playPickupSound():
	# decomp Items/Exclusive/BadgerSpirit.gd:30 Sound.playSound_process(pickupSound, - 12, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

	# decomp Items/Exclusive/BadgerSpirit.gd:34 Sound.playSound(dropSound, volume - 6, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
func _readyInit():
	._readyInit()
	healthThreshold = getP("healtht") / 100.0
	manaNeeded = int(getP("manat"))
