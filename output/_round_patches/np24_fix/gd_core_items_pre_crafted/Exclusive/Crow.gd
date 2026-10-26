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
	# ★ kernel_r2c 移植补抽：原版此行含 Util.randPitch(0.1)（=randf_range(0.9, 1.1)，
	#   Util.gd:685-686），转译期随音效行被剥——链消耗丢失（activate() 虚分发
	#   后此覆写生效，抽面必须与原版一致）。
	ctx.rng.randf_range(0.9, 1.1)

func _readyInit():
	._readyInit()
	speedBonus = getP("speed") / 100.0
	maxActivations = int(getP("max"))
	luck = int(getP("luck"))
