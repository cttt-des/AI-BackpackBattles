extends Item

onready var coldAmount: = int(getP3())

var maxUses: int
var uses: int

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

func canAffect(item):
	return item.hasType(Type.Ice) and not item.isA(descriptor)

func onPrepare():
	uses = 0
	maxUses = int(getP1()) + getNumAffectedItems()

func doCooldownEffect():
	if uses < maxUses:
		uses += 1
		var dam = descriptor.minDam
		var damageRes = dealEffectDamage(dam)
		giveStacksTemporary(opponent(), Game.EventType.Cold, 
			coldAmount, getP_m("dur_cold"), damageRes.event)
		if uses == maxUses:
			onAfterEffectFinished()
		else:
			activate()
