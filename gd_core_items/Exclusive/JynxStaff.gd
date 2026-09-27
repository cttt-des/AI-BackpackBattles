extends Weapon
var numActivations: int
var manaCost
var permDamBonus
var speedBonus
var maxActivations
var luckRemoval

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	numActivations = 0


func onPreDealDamage_early(damageRes: CoreDamageResult):
	var event = tryUseMana(manaCost)
	if event != null:
		addBonusDamage(permDamBonus)
		if numActivations < maxActivations:
			for item in getAffectedItems():
				
				item.addSpeed(speedBonus)
				
			numActivations += 1
			
		if opponent().getLucky() > 0:
			removeLucky(luckRemoval)
		

func _readyInit():
	._readyInit()
	manaCost = int(getP("manat"))
	permDamBonus = getP("dam")
	speedBonus = getP("speed") / 100.0
	maxActivations = int(getP("max"))
	luckRemoval = int(getP("luck"))
