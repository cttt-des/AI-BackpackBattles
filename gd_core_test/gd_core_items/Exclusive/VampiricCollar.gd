extends RangerCollar
var affectedItems_dict: Dictionary
var maxLifesteal

func canAffect(item):
	return item.canDamage()


func onPrepare():
	if not affectedItems.empty():
		connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")
		connectForCombat(opponent(), "character_attacked", "onOpponentAttacked")
	
	affectedItems_dict = ctx.util.arrayAsIndexDict(affectedItems)
	

func onVampirismChanged(amount, event):
	for item in affectedItems:
		item.changeCritChancePercent(amount * getChance())


func onOpponentAttacked(damageRes: CoreDamageResult):
	if (damageRes.getDamage() > 0 and 
		damageRes.damageSource.canApplyLifesteal() and 
		damageRes.damageSource.origin in affectedItems_dict):
			
		var lifestealFactor = getP_m("lifesteal") / 100.0 * character().getLucky()
		if lifestealFactor > 0:
			lifestealFactor = min(lifestealFactor, maxLifesteal)
			var lifesteal = max(1, damageRes.damage * lifestealFactor)
			heal(lifesteal, damageRes.event)

func _readyInit():
	._readyInit()
	maxLifesteal = getP("max") / 100.0
