extends Item

func canAffect(item):
	return item.canBeEmpowered()

func canAffect_secondary(item):
	return item.hasType(Type.Vampiric)

func onPrepare():
	character().addHealingEfficiency(getP3() / 100.0)

	
	for weapon in getAffectedItems():
		connectForCombat(weapon, "attacked", "onAffectedAttacked")

func onCombatStart():
	giveVampirism(getP1())
	activate()

func onAffectedAttacked(damageRes: DamageResult):
	if damageRes.hasHit():
		var bonusLifesteal = getNumAffectedItems(Affected.Secondary) * getP_m("lifesteal_scaling")
		heal(ceil(damageRes.damage * (getP_m("lifesteal") + bonusLifesteal) / 100.0), 
			damageRes.event)










