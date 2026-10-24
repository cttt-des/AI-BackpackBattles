extends Weapon

const stunParticles = preload("res://Items/Particles/StunParticles.tscn")

onready var extraAccuracy = getP2()
onready var battleRageSpeed = getP4() / 100.0

func canAffect(item):
	return item.canDamage()

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		addCritChancePercent(getChance2())
		addAccuracy(extraAccuracy)
		for item in getAffectedItems():
			item.addCritChancePercent(getChance2())
			if item.isWeapon():
				item.addAccuracy(extraAccuracy)
		if rollChance():
			stun(getP_m("dur_stun"), damageRes.event)
			var particles = ObjectPool.particleOneShot(stunParticles, sprite)
			particles.position = Vector2(0, - 60)

func onPrepare():
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")

func onBattleRageStarted(_event):
	addSpeed(battleRageSpeed)

func onBattleRageEnded(_event):
	reduceSpeed(battleRageSpeed)
