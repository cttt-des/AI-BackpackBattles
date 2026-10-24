extends Weapon

const stunParticles = preload("res://Items/Particles/StunParticles.tscn")

onready var manaNeeded: = int(getP("manat"))
onready var effectDmg: = int(getP("dam"))
onready var blind: = int(getP("blind"))

var effectDmgSource: DamageSource

func _ready():
	effectDmgSource = DamageSource.new().init(self, 
		DamageSource.Type.Effect, effectDmg)

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		if rollChance():
			stun(getP_m("dur_stun"), damageRes.event)
			var particles = ObjectPool.particleOneShot(stunParticles, sprite)
			particles.position = Vector2(175, - 144)
		
		if character().getMana() >= manaNeeded:
			var event = useMana(manaNeeded, damageRes.event)
			dealEffectDamage(effectDmg, event, effectDmgSource)
			var duration = getP_m("dur_blind")
			giveStacksTemporary(opponent(), Game.EventType.Blind, 
				blind, duration, event)
