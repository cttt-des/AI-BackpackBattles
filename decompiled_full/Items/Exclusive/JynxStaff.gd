extends Weapon

const activationParticles_jynx = preload("res://Items/Particles/JynxActivationParticles.tscn")
const activationParticles_staff = preload("res://Items/Particles/MagicStaffActivationParticles.tscn")

var numActivations: int

onready var manaCost: = int(getP("manat"))
onready var permDamBonus = getP("dam")
onready var speedBonus = getP("speed") / 100.0
onready var maxActivations: = int(getP("max"))
onready var luckRemoval: = int(getP("luck"))

func canAffect(item):
	return item.hasCooldown()

func onPrepare():
	numActivations = 0

func onPreDealDamage_early(damageRes: DamageResult):
	var event = tryUseMana(manaCost)
	if event != null:
		addBonusDamage(permDamBonus)
		if numActivations < maxActivations:
			for item in getAffectedItems():
				
				item.addSpeed(speedBonus)
				
			numActivations += 1
			var particles1 = ObjectPool.particleOneShot(activationParticles_jynx, self)
			particles1.position = Vector2(30, - 150)
			
		if opponent().getLucky() > 0:
			removeLucky(luckRemoval)
		
		var particles2 = ObjectPool.particleOneShot(activationParticles_staff, self)
		particles2.global_position = specificDragParticles[0].global_position
