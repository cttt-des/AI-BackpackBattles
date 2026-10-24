extends Food

const glowingTexture = preload("res://Items/Sprites/Pumpkin_glowing.png")
const stunParticles = preload("res://Items/Particles/StunParticles.tscn")

onready var heat: = int(getP("heat"))
onready var normalTexture = sprite.texture

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		var res = dealDamage()
		activate(res)

func onPrepare():
	descriptor.activationAni = ActivationAni.Throw
	connectForCombat(Game.combatTimer, "fatigue_start", "onFatigueStarted")

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		stun(getP_m("dur_stun"), damageRes.event)
		var particles = ObjectPool.particleOneShot(stunParticles, sprite)
		particles.position = Vector2(110, - 30)

func onFatigueStarted():
	setTexture(glowingTexture)
	giveHeat(heat)
	activate()

func onShopEntered():
	setTexture(normalTexture)
