extends Item
var nonMusicalItems: Array
var activateIndex: int
var options: Array
var speedPerItem
var cdAdvance
var healAmp
var buffs
var cold

func canAffect(item):
	return true


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Musical)


func onPrepare():
	activateIndex = 0
	nonMusicalItems.clear()
	for item in inventory.getItems():
		if ( not item.hasType(CoreConst.Type.Musical) and 
			item.hasCooldown()):
			nonMusicalItems.push_back(item)
	
	if not nonMusicalItems.empty():
		nonMusicalItems.shuffle()
		
		for item in getAffectedItems(CoreConst.Affected.Secondary):
			connectForCombat(item, "activated", "onItemActivated")
	
	addSpeed(speedPerItem * getNumAffectedItems())
	
	character().addHealingEfficiency(healAmp)
	
	for item in inventory.getItems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())
	
	options = [0, 1, 2]
	

func onItemActivated(event):
	
	
	while true:
		if nonMusicalItems.empty():
			return
		
		var item = nonMusicalItems[activateIndex]
		
		if item.isCooldownActive():
			
			
			item.advanceCooldownPercent(cdAdvance)
			activateIndex = (activateIndex + 1) % nonMusicalItems.size()
			break
		else:
			
			
			nonMusicalItems.erase(item)
			if not nonMusicalItems.empty():
				activateIndex %= nonMusicalItems.size()


func doCooldownEffect():
	var rng = ctx.util.pickRandomElement(options)
	if rng == 0:
		heal()
	elif rng == 1:
		giveRandomBuffs(buffs)
	else:
		inflictCold(cold)
	
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)
	

func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume
	# ★ kernel_r2c 移植补抽：原版此行含 Util.randPitch(0.15)（=randf_range(0.85, 1.15)，
	#   Util.gd:685-686），转译期随音效行被剥——链消耗丢失（activate() 虚分发
	#   后此覆写生效，抽面必须与原版一致）。
	ctx.rng.randf_range(0.85, 1.15)

func _readyInit():
	._readyInit()
	speedPerItem = getP("speed") / 100.0
	cdAdvance = getP("advance")
	healAmp = getP("healamp") / 100.0
	buffs = int(getP("buffs"))
	cold = int(getP("cold"))
