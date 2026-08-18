extends Weapon

const stunParticles = preload("res://Items/Particles/StunParticles.tscn")

onready var activationParticles = $Icon / ActivationParticles
onready var heatThreshold: = int(getP1())

var heatThresholdReached: bool
var hasStunned: bool

func onPrepare():
	setState(false)
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")

func onHeatChanged(amount, event):
	if not heatThresholdReached:
		if character().getHeat() >= heatThreshold:
			setState(true, false, event)
	elif character().getHeat() < heatThreshold:
		setState(false, false, event)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		hasStunned = false
		var res: DamageResult = dealDamage()
		if hasStunned:
			activate(res, false, false, ActivationAni.Tackle)
		else:
			activate(res, false)
		var ani = createAnimation()
		ani.randomizePosition()
		if res.hasHit():
			if hasStunned:
				ani.animation.play("RubyWhelpTackle")
			else:
				ani.animation.play("RubyWhelp")
		else:
			ani.animation.play("RubyWhelpMiss")

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		giveHeat(1, damageRes.event)
		if heatThresholdReached:
			if rollChance():
				stun(getP_m("dur_stun"), damageRes.event)
				hasStunned = true
				var particles = ObjectPool.particleOneShot(stunParticles, sprite)
				particles.position = Vector2(85, 64)

func onShopEntered():
	onStateChanged(false)

func onStateChanged(_heatThresholdReached):
	if _heatThresholdReached:
		activationParticles.activate()
	else:
		activationParticles.deactivate()
	
	heatThresholdReached = _heatThresholdReached

func getCraftingOffset(forDirection):
	match forDirection:
		FaceDirection.UP:
			return Vector2(0, - 1)
		FaceDirection.DOWN:
			return Vector2.ZERO
		FaceDirection.LEFT:
			return Vector2( - 1, 0)
		FaceDirection.RIGHT:
			return Vector2.ZERO
