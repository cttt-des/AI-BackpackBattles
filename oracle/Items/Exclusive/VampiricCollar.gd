extends RangerCollar

onready var maxLifesteal: = getP("max") / 100.0
var affectedItems_dict: Dictionary

func canAffect(item):
	return item.canDamage()

func onPrepare():
	if not affectedItems.empty():
		connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")
		connectForCombat(opponent(), "character_attacked", "onOpponentAttacked")
	
	affectedItems_dict = Util.arrayAsIndexDict(affectedItems)
	
func onVampirismChanged(amount, event):
	for item in affectedItems:
		item.changeCritChancePercent(amount * getChance())

func onOpponentAttacked(damageRes: DamageResult):
	if (damageRes.getDamage() > 0 and 
		damageRes.damageSource.canApplyLifesteal() and 
		damageRes.damageSource.origin in affectedItems_dict):
			
		var lifestealFactor = getP_m("lifesteal") / 100.0 * character().getLucky()
		if lifestealFactor > 0:
			lifestealFactor = min(lifestealFactor, maxLifesteal)
			var lifesteal = max(1, damageRes.damage * lifestealFactor)
			heal(lifesteal, damageRes.event)
