extends Item
var numActivations: int
var speedBonus
var maxActivations
var bonusHeal

func canAffect(item):
	return (item.hasCooldown() or item.gainsBuffs() or item.canHealOrLifesteal())


func onPrepare():
	numActivations = 0


func doCooldownEffect():
	if numActivations < maxActivations:
	
		for item in getAffectedItems():
			item.addSpeed(speedBonus)
			item.changeAmplificiationChancePercent_allBuffs(getChance())
			item.changeHealAmp(bonusHeal)
		
		numActivations += 1
		
		if numActivations == maxActivations:
			onAfterEffectFinished()
		else:
			activate()


func playPickupSound():
	var pitch = ctx.rng.randf_range(0.8, 1.0)


func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = ctx.rng.randf_range(0.8, 1.0)

func _readyInit():
	._readyInit()
	speedBonus = getP("speed") / 100.0
	maxActivations = int(getP("max"))
	bonusHeal = getP("healamp") / 100.0
