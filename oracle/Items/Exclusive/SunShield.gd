extends Shield

var blockAcc: int
var bonusDamagePerTick: int
onready var damagePerTick: int = getP4()
onready var blockPerTick: int = getP3()
onready var activationParticles = $Icon / ActivationParticles

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)
	damageSource.unsetFlag(DamageSource.Flags.CanCrit)
	
func canAffect(item):
	return item.canBlock()

func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "gave_block", "onItemGaveBlock")
	bonusDamagePerTick = 0

func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	activate()

func onItemGaveBlock(amount, event):
	blockAcc += amount
	var ticks = blockAcc / blockPerTick
	if ticks > 0:
		blockAcc %= blockPerTick
		var dam = ticks * (damagePerTick + bonusDamagePerTick)
		var damageRes = dealEffectDamage(dam, event)
		miniActivate()
		activationParticles.activate()



func canBlockDamageRes(damageRes: DamageResult) -> bool:
	return damageRes.triggerOnAttacked()

func addBonusDamageOnTick(dam):
	bonusDamagePerTick += dam
