extends Weapon
var numActivations: int
var activationParticles
var manaCost: int
var heatCost: int
var damBonus: int

func onPrepare():
	numActivations = 0


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if character().getHeat() >= heatCost:
		var event = tryUseMana(manaCost)
		if event != null:
			useHeat(heatCost, event)
			addBonusDamage(damBonus)
			numActivations += 1


func onShopEntered():
	pass

func _readyInit():
	._readyInit()
	manaCost = getP1()
	heatCost = getP2()
	damBonus = getP3()
	pass

