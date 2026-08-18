extends Item

var activated: bool
var coldInflicted: int

onready var cold: = getP("cold")
onready var maxCold: = getP("max")
const activationParticles1 = preload("res://Items/Exclusive/Particles/SpellScrollIceActivationParticles1.tscn")
const activationParticles2 = preload("res://Items/Exclusive/Particles/SpellScrollIceActivationParticles2.tscn")

func canAffect(item):
	return item.hasType(Type.Shield) or (item.hasType(Type.Armor) and item.canActivate())

func onPrepare():
	activated = false
	connectForCombat(character(), "pre_take_damage_late", "onCharacterAttacked")
	
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onShieldOrArmorActivated")
	coldInflicted = 0

func onCharacterAttacked(damageRes):
	if not activated:
		if damageRes.willBeLethal(character()):
			var opponentCold = opponent().getCold()
			if opponentCold > 0:
				activated = true
				opponent().loseCold(opponentCold, self, damageRes.event)
				giveBlock(round(getBlock() * opponentCold), true, damageRes.event)
				consume()
				ObjectPool.particleOneShot(activationParticles1, self)
				ObjectPool.particleOneShot(activationParticles2, self)

func onShieldOrArmorActivated(event):
	if coldInflicted < maxCold and rollChance():
		coldInflicted = min(cold, maxCold - coldInflicted)
		inflictCold(cold, event)
		miniActivate()
