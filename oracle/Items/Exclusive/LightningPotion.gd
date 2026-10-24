extends Potion

onready var blind: = int(getP("blind"))
onready var lightningAni = $Icon / Zap / AnimationPlayer

func _ready():
	damageSource = DamageSource.new().setItem(self)

func canAffect_secondary(item):
	return item.hasType(Type.Holy)

func onTriggerPotion(triggerEvent = null):
	var dam = descriptor.minDam
	var res = dealEffectDamage(dam)
	
	
	giveStacksTemporary(opponent(), Game.EventType.Blind, 
		blind, getP_m("dur_blind"), triggerEvent)
	
	heal(getP_m("heal") * getNumAffectedItems(Affected.Secondary))

func onPrepare():
	baseCooldownOverride = Util.rng.randf_range(
		getBaseCooldownIndex(0), getBaseCooldownIndex(1))

	

func doCooldownEffect():
	consumePotion(null, false)
	onAfterEffectFinished()

func fill():
	lightningAni.play("Fill")
	.fill()

func empty():
	lightningAni.play("Drink")
	.empty()
