extends "res://Items/Exclusive/ForestFriend.gd"

const activationParticles = preload("res://Items/Exclusive/Particles/HedgehogActivationParticles.tscn")

var hasActivated: bool

onready var spikes: = int(getP("spikes"))
onready var damagePerSpike = getP("dam_spikes")
onready var healthThreshold = getP("healtht") / 100.0 - 0.0001

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

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
	ObjectPool.particleOneShot(activationParticles, sprite)

func getTriggerPriority() -> int:
	return Priority.High + 3
