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
	# ★ kernel_r2c 移植补抽：原版此行含 Util.randPitch(0.1)（=randf_range(0.9, 1.1)，
	#   Util.gd:685-686），转译期随音效行被剥——链消耗丢失（activate() 虚分发
	#   后此覆写生效，抽面必须与原版一致）。
	ctx.rng.randf_range(0.9, 1.1)

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	mana = int(getP("mana"))
	fatigueMana = int(getP("fatiguemana"))
