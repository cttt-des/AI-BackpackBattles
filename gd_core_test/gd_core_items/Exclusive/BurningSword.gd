extends Weapon
var heatCounter = 0
var particleReadyTime: = 0.0
var heatOnHit: int
var heatNeeded: int

func canAffect(item):
	return item.canBeEmpowered()


func onPrepare():
	heatCounter = 0
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")


func onHeatChanged(amount, _event):
	if amount > 0:
		heatCounter += amount
		var bonus = heatCounter / heatNeeded
		if bonus > 0:
			var bonusDamage = getP3() * bonus
			for item in getAffectedItems():
				item.addBonusDamage(bonusDamage)
			addBonusDamage(bonusDamage)
			
			if ctx.time >= particleReadyTime:
				particleReadyTime = ctx.time + 0.1
		
		heatCounter %= heatNeeded


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		giveHeat(heatOnHit)

func _readyInit():
	._readyInit()
	heatOnHit = getP1()
	heatNeeded = getP2()
