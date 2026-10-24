extends Item

const activationParticles = preload("res://Items/Exclusive/Particles/UkuleleActivationParticles.tscn")
const buffParticles = preload("res://Items/Exclusive/Particles/UkuleleBuffParticles.tscn")

const pickupSound = preload("res://Assets/Sound/Ukulele1.ogg")
const dropSound = preload("res://Assets/Sound/Ukulele2.ogg")

onready var speedPerItem: = getP("speed") / 100.0
onready var cdAdvance: = getP("advance")
onready var healAmp: = getP("healamp") / 100.0
onready var buffs: = int(getP("buffs"))
onready var cold: = int(getP("cold"))

var nonMusicalItems: Array
var activateIndex: int
var options: Array

func canAffect(item):
	return true

func canAffect_secondary(item):
	return item.hasType(Type.Musical)

func onPrepare():
	activateIndex = 0
	nonMusicalItems.clear()
	for item in inventory.getItems():
		if ( not item.hasType(Type.Musical) and 
			item.hasCooldown()):
			nonMusicalItems.push_back(item)
	
	if not nonMusicalItems.empty():
		nonMusicalItems.shuffle()
		
		for item in getAffectedItems(Affected.Secondary):
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
			ObjectPool.particleOneShot(buffParticles, item)
			break
		else:
			
			
			nonMusicalItems.erase(item)
			if not nonMusicalItems.empty():
				activateIndex %= nonMusicalItems.size()

func doCooldownEffect():
	var rng = Util.pickRandomElement(options)
	var particles = ObjectPool.particleOneShot(activationParticles, self)
	if rng == 0:
		heal()
		particles.modulate = Color(0.632356, 0.978516, 0.582905)
	elif rng == 1:
		giveRandomBuffs(buffs)
		particles.modulate = Color(1, 0.390625, 0.840515)
	else:
		inflictCold(cold)
		particles.modulate = Color(0.266667, 0.972549, 1)
	
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)
	
func playPickupSound():
	Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.15))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 4, Util.randPitch(0.15))
