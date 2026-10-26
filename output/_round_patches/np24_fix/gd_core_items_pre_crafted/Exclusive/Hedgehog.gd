extends "res://gd_core_items/Exclusive/ForestFriend.gd"
var hasActivated: bool
var spikes
var damagePerSpike
var healthThreshold

func doCooldownEffect():
	var dam = descriptor.minDam + character().getSpikes() * damagePerSpike
	var res = dealEffectDamage(dam)
	activate(res)


func onPrepare():
	hasActivated = false
	connectForCombat(character(), "character_damaged", "onDamaged")


func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		onHPLow(event)
		
		
		miniActivate()


func onHPLow(event):
	giveSpikes(spikes, event)
	giveBlock(getBlock(), true, event)
	spawnSpikeParticles()


func spawnSpikeParticles():
	pass


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 3

func _readyInit():
	._readyInit()
	spikes = int(getP("spikes"))
	damagePerSpike = getP("dam_spikes")
	healthThreshold = getP("healtht") / 100.0 - 0.0001
	damageSource = CoreDamageSource.new().setItem(self)

