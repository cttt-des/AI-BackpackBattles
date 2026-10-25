extends Weapon
var gaveBlock: bool
var coldOnHit: int
var coldThreshold: int
var damReduction

func onPrepare():
	gaveBlock = false
	connectForCombat(opponent(), "character_cold_changed", "onOpponentColdChanged")


func onOpponentColdChanged(amount, event):
	if not gaveBlock and opponent().getCold() >= coldThreshold:
		gaveBlock = true
		giveBlock(getBlock(), true, event)
		opponent().changeEffectDamageFactor( - damReduction)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		inflictCold(coldOnHit)

func _readyInit():
	._readyInit()
	coldOnHit = getP("cold")
	coldThreshold = getP("coldt")
	damReduction = getP("damfactor") / 100.0
