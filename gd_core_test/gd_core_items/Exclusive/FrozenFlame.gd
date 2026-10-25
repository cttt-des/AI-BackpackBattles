extends Item
var affected2Item = null
var heatCounter: int
var gatedItems = {
	"Spell Scroll Frostbolt": 2, 
	"Book of Ice": 2, 
	"Frostbite": 1, 
	"Frozen Buckler": 1, 
	"Ice Armor": 1, 
	"Ice Dragon": 1, 
	"Spell Scroll Ice": 1, 
	"Magic Mirror": 1, 
	"Ice Flower": 1, 
	"Devouring Sphere": 1, 
	"Snowmaster": 1
}
var heatNeeded: int
var coldPerHeat: int
var critSeverityPerCold

func canAffect(item):
	return item.hasType(CoreConst.Type.Ice)


func canAffect_secondary(item):
	return item.canDamage()


func onPrepare():
	heatCounter = 0
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")
	
	affected2Item = getFirstAffectedItem(CoreConst.Affected.Secondary)
	if affected2Item:
		connectForCombat(opponent(), "character_cold_changed", "onOpponentColdChanged")


func onCombatStart():
	var numAffected = getNumAffectedItems()
	if numAffected > 0:
		giveBlock(numAffected * getBlock())
	activate()


func onHeatChanged(amount, event):
	if amount > 0:
		heatCounter += amount
		var relHeat = float(heatCounter) / heatNeeded
		var cold = int(relHeat) * coldPerHeat
		heatCounter %= heatNeeded
		if cold > 0:
			inflictCold(cold, event)
			showCooldownSmooth(float(heatCounter) / heatNeeded, true)
		else:
			showCooldownSmooth(relHeat, false)


func onOpponentColdChanged(amount, _event):
	
	affected2Item.changeCritChancePercent(amount * getChance())
	affected2Item.addCritSeverity(amount * critSeverityPerCold)


func getGatedDescriptor(rarity) -> CoreItemData:
	return null

func getRelatedItemColumns() -> int:
	return 4


func getRelatedItemHeight() -> int:
	return 200

func _readyInit():
	._readyInit()
	heatNeeded = getP("heat")
	coldPerHeat = getP("cold")
	critSeverityPerCold = getP("critdam") / 100.0
	pass

