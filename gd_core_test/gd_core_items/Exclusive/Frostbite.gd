extends Weapon
var gaveVampirism: bool
var damagePerCold
var coldNeeded
var vampirism

func onPrepare():
	gaveVampirism = false
	connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")
	connectForCombat(opponent(), "character_cold_changed", "onOpponentColdChanged")


func onVampirismChanged(amount, _event):
	changeVaryingDamage(amount)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		inflictCold(getP1())


func onOpponentColdChanged(amount, event):
	changeVaryingDamage(damagePerCold * amount)
	
	if not gaveVampirism and opponent().getCold() >= coldNeeded:
		gaveVampirism = true
		giveVampirism(vampirism, event)

func _readyInit():
	._readyInit()
	damagePerCold = getP2()
	coldNeeded = int(getP3())
	vampirism = int(getP4())
