extends Item
var numActivations: int
var speedBonus
var maxActivations
var luck

func canAffect(item):
	return item.hasCooldown() or item.inflictsDebuffs()


func onPrepare():
	numActivations = 0


func doCooldownEffect():
	if numActivations < maxActivations:
		for item in getAffectedItems():
			
			item.addSpeed(speedBonus)
			item.changeAmplificiationChancePercent_allDebuffs(getChance())
			
		numActivations += 1
	
	var luckToRemove = min(luck, opponent().getLucky())
	if luckToRemove > 0:
		stealStack(CoreConst.EventType.Lucky, luckToRemove)
	
	activate()


func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

func _readyInit():
	._readyInit()
	speedBonus = getP("speed") / 100.0
	maxActivations = int(getP("max"))
	luck = int(getP("luck"))
