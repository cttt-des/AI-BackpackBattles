extends Item
var healthUsed
var effectDmg
var availableBuffs

func doCooldownEffect():
	if character().getCurrentHealth() > healthUsed:
		var event = character().loseHealth(healthUsed, self)
		var dam = descriptor.minDam
		var res = dealEffectDamage(dam, event)
		
		var maxBuffs = getMostStacks(character(), availableBuffs.keys())
		var buffToGive = ctx.util.pickRandomElement(maxBuffs)
		var amount = availableBuffs[buffToGive]
		giveStacks(character(), buffToGive, amount, event)
		
		
	activate()


func canAffect(item):
	return item.hasType(CoreConst.Type.Dark)


func onPrepare():
	var bonusEffectDmg = 0.0
	for item in getAffectedItems():
		if item.hasType(CoreConst.Type.Spell):
			bonusEffectDmg += effectDmg * 2.0
		else:
			bonusEffectDmg += effectDmg
	
	character().changeEffectDamageFactor(bonusEffectDmg)

func _readyInit():
	._readyInit()
	healthUsed = int(getP("healtht"))
	effectDmg = getP("dam") / 100.0
	availableBuffs = {
	CoreConst.EventType.Mana: int(getP("mana")), 
	CoreConst.EventType.Lucky: int(getP("luck")), 
	CoreConst.EventType.Regeneration: int(getP("regen"))
}
	damageSource = CoreDamageSource.new().setItem(self)

