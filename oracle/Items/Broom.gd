extends Weapon

const blindParticles = preload("res://Items/Particles/DirtParticles.tscn")

onready var bonusDamPerMiss = int(getP1())

var broomBonusDam = 0
var onMissReadyTime = 0.0

func onPrepare():
	connectForCombat(character(), "character_attacked", "onAttacked")

func onAttacked(damageRes):
	if not damageRes.hasHit():
		addBonusDamage(bonusDamPerMiss)
		broomBonusDam += bonusDamPerMiss




func attack(event = null):
	.attack(event)
	if broomBonusDam != 0:
		reduceBonusDamage(broomBonusDam, false)
		broomBonusDam = 0


func onDealtDamage(damageRes):
	if damageRes.hasHit():
		if rollChance():
			inflictBlind(1, damageRes.event)
			var particles = ObjectPool.particleOneShot(blindParticles, sprite)
			particles.position = Vector2(0, 230)
			particles.global_rotation = 0

func onShopEntered():
	broomBonusDam = 0
