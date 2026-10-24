extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/NullBladeActivationParticles.tscn")

onready var luckNeeded: = int(getP("luckt"))
onready var regenNeeded: = int(getP("regent"))
onready var dam: = int(getP("dam"))
onready var buffs: = int(getP("buffs"))
onready var speedBonus: = getP("speed") / 100.0
onready var distortion = $Icon / Distortion

func _ready():
	distortion.hide()

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		if character().getLucky() >= luckNeeded:
			useLucky(luckNeeded)
			damageRes.damage += dam
			addBonusDamage(dam)
			var particles = ObjectPool.particleOneShot(activationParticles, sprite)
			particles.rotation_degrees = 0
			particles.position = Vector2(0, 200)
			
		if character().getRegeneration() >= regenNeeded:
			useRegeneration(regenNeeded)
			removeRandomBuffs(buffs)
			if opponent().getBuffStacks() == 0:
				addSpeed(speedBonus)
			
			var particles = ObjectPool.particleOneShot(activationParticles, sprite)
			particles.rotation_degrees = 180
			particles.position = Vector2(0, - 200)

func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)
	distortion.show()

func drop():
	var res = .drop()
	distortion.hide()
	return res
