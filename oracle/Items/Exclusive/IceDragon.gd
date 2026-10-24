extends Weapon

var gaveBlock: bool

onready var coldOnHit: int = getP("cold")
onready var coldThreshold: int = getP("coldt")
onready var damReduction: = getP("damfactor") / 100.0

func onPrepare():
	gaveBlock = false
	connectForCombat(opponent(), "character_cold_changed", "onOpponentColdChanged")

func onOpponentColdChanged(amount, event):
	if not gaveBlock and opponent().getCold() >= coldThreshold:
		gaveBlock = true
		giveBlock(getBlock(), true, event)
		opponent().changeEffectDamageFactor( - damReduction)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		inflictCold(coldOnHit)
