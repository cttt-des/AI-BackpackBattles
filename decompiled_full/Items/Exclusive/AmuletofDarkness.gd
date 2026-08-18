extends Item

const amuletColor = Color(0.580392, 0.266667, 0.960784)
const activationParticles = preload("res://Items/Exclusive/Particles/AmuletofDarknessParticles.tscn")

onready var damageThreshold: = int(getP("damt"))
var damageAcc: int

func _ready():
	damageSource = DamageSource.new().setItem(self)
	specificDragParticles[0].self_modulate = amuletColor

func canAffect(item):
	return item.canActivate()

func onPrepare():
	damageAcc = 0
	connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")
	
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")

func onItemActivated(event):
	if rollChance():
		var dam = descriptor.minDam
		var res = dealEffectDamage(dam)
		activate()
		var particles = ObjectPool.particleOneShot(activationParticles, self)
		move_child(particles, 0)

func onOpponentDamaged(damageRes: DamageResult):
	if damageRes.hasHit() and damageRes.damageSource.isEffectDamage():
		damageAcc += damageRes.damage
		
		var proccs = damageAcc / damageThreshold
		if proccs > 0:
			damageAcc %= damageThreshold
			inflictRandomDebuffs(proccs)
			miniActivate()
