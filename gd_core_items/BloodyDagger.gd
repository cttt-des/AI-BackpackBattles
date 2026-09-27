extends Dagger
var vampirismStacks: int

func canAffect(item):
	return item.hasType(CoreConst.Type.Vampiric)
	

func onPrepare():
	vampirismStacks = 0


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if vampirismStacks < getP2():
			giveVampirism(getP1())
			vampirismStacks += getP1()
	
		var numAffected = getNumAffectedItems()
		if numAffected > 0:
			heal(numAffected * getP_m("heal"))

func _readyInit():
	._readyInit()
	pass
