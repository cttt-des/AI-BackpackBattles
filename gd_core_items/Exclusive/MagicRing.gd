extends Item
enum TriggerType{
	StartOfBattle = 0, 
	Every = 1, 
	PlayerLow = 2, 
	OppoLow = 3
}
var stackToTypes = {
	CoreConst.EventType.Lucky: CoreConst.Type.Nature, 
	CoreConst.EventType.Spikes: CoreConst.Type.Nature, 
	CoreConst.EventType.Regeneration: CoreConst.Type.Holy, 
	CoreConst.EventType.Heat: CoreConst.Type.Fire, 
	CoreConst.EventType.Vampirism: CoreConst.Type.Vampiric, 
	CoreConst.EventType.Empower: CoreConst.Type.Holy, 
	CoreConst.EventType.Mana: CoreConst.Type.Magic, 
	CoreConst.EventType.Blind: CoreConst.Type.Dark, 
	CoreConst.EventType.Cold: CoreConst.Type.Ice, 
	CoreConst.EventType.Poison: CoreConst.Type.Nature, 
}
var stackToColor = {
	CoreConst.EventType.Lucky: Color(0.329826, 1, 0.263672), 
	CoreConst.EventType.Spikes: Color(0.700867, 1, 0.263672), 
	CoreConst.EventType.Regeneration: Color(1, 0.388672, 0.696724), 
	CoreConst.EventType.Heat: Color(1.1, 0.44, 0.24), 
	CoreConst.EventType.Vampirism: Color(0.900391, 0.04924, 0.04924), 
	CoreConst.EventType.Empower: Color(0.955078, 0.665003, 0.341366), 
	CoreConst.EventType.Mana: Color(0.257812, 0.330292, 1), 
	CoreConst.EventType.Blind: Color(0.569776, 0.196078, 1), 
	CoreConst.EventType.Cold: Color(0.196078, 0.952895, 1), 
	CoreConst.EventType.Poison: Color(0.008865, 0.648438, 0.176254)
}
var effects: Array
var effectDict: Dictionary
var gainedStacks: int
var playerLowTriggered: = false
var oppoLowTriggered: = false
var ringTypes: Array
var textEffect: int
var numEffects
var healthThreshold
var opponentHealthThreshold
var stones
var symbols

func hasCooldown() -> bool:
	return TriggerType.Every in effectDict


func hasStartofBattle() -> bool:
	return TriggerType.StartOfBattle in effectDict


func onPrepare():
	playerLowTriggered = false
	oppoLowTriggered = false
	
	if TriggerType.PlayerLow in effectDict:
		connectForCombat(character(), "character_damaged", "onDamaged")
	
	if TriggerType.OppoLow in effectDict:
		connectForCombat(opponent(), "character_damaged", "onOppoDamaged")


func onCombatStart():
	for effect in effectDict[TriggerType.StartOfBattle]:
		giveStacksFromEffect(effect)


func doCooldownEffect():
	for effect in effectDict[TriggerType.Every]:
		giveStacksFromEffect(effect)


func onDamaged(_healthChange, event):
	if playerLowTriggered: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		playerLowTriggered = true
		for effect in effectDict[TriggerType.PlayerLow]:
			giveStacksFromEffect(effect, event)


func onOppoDamaged(_healthChange, event):
	if oppoLowTriggered: return
	
	var relHealth = opponent().getRelativeHealth()
	if relHealth < opponentHealthThreshold:
		oppoLowTriggered = true
		for effect in effectDict[TriggerType.OppoLow]:
			giveStacksFromEffect(effect, event)


func giveStacksFromEffect(effect, triggerEvent = null):
	var target
	if CoreConst.isBuff(effect.stackType):
		target = character()
	else:
		target = opponent()
	
	var stackName = ctx.event_type_keys[effect.stackType].to_lower()
	var paramScale = getP(str("scale", effect.triggerType + 1))
	giveStacks(target, effect.stackType, 
		getScaledParam(stackName, paramScale), triggerEvent)
	
	activate()



func sortEffects():
	gainedStacks = 0
	effectDict.clear()
	ringTypes.clear()
	
	var effectI = 0
	for effect in effects:
		effectI += 1
		
	if not isOnlyForDisplay():
		
		for effect in effects:
			ctx.util.dictAppend(effectDict, effect.triggerType, effect)
			
			gainedStacks |= 2 << (effect.stackType - CoreConst.EventType.Lucky)
			
			var newType = stackToTypes[effect.stackType]
			if not newType in ringTypes:
				ringTypes.push_back(newType)
			
		
		if inventory != null:
			inventory.onItemTypeChanged(self)
	else:
		pass


func getTypes() -> Array:
	return .getTypes() + ringTypes


func hasType(type: int) -> bool:
	return type in ringTypes or .hasType(type)


func getNumStaticTypes() -> int:
	return .getNumStaticTypes() + ringTypes.size()


func gainsStack(stackType) -> bool:
	return gainedStacks & stackType


func gainsBuffs() -> bool:
	return gainedStacks & CoreConst.Stack.Buff


func inflictsDebuffs() -> bool:
	return gainedStacks & CoreConst.Stack.Debuff


func getTextEffect() -> int:
	return textEffect


func randEffects(clearIfOnlyDisplay = true):
	effects.clear()
	
	for i in numEffects:
		var effect = RingEffect.new()
		effects.push_back(effect)
		effect.triggerType = ctx.rng.randi_range(0, 3)
		effect.stackType = ctx.rng.randi_range(CoreConst.EventType.Lucky, 
			CoreConst.EventType.Cold)
		
	
	sortEffects()
	
	if clearIfOnlyDisplay and isOnlyForDisplay():
		effects.clear()


func getScaledParam(stackName: String, paramScale: float) -> float:
	return round(getP(stackName) * paramScale)


func isOnlyForDisplay() -> bool:
	return (ownerType == CoreConst.Owner.ItemLibrary or 
		ownerType == CoreConst.Owner.InfoPanelIcon or 
		ownerType == CoreConst.Owner.Tooltip or 
		ownerType == CoreConst.Owner.RecipeBook or 
		ownerType == CoreConst.Owner.BuildViewerIcon)


func getDescription(wrapInColor = true) -> String:
	return ""

func copyFrom(otherRing):
	setData(otherRing.getData())


func getData():
	pass

func setData(_data):
	pass

func persistDataInShop() -> bool:
	return true


func getDataPersistent(bitStream):
	for effect in effects:
		effect.pushEncoded(bitStream)





func getDataPersistentBits():
	return numEffects * (2 + 4)



func onCraftedFrom(baseItem, ingredients):
	effects.clear()
	effects.append_array(baseItem.effects)
	effects.append_array(ingredients[0].effects)
	
	
	effects.remove(ctx.rng.randi_range(0, 3))
	
	sortEffects()


















func _readyInit():
	._readyInit()
	numEffects = int(getP("effects"))
	healthThreshold = getP("healtht") / 100.0
	opponentHealthThreshold = getP("healtht_opp") / 100.0
	stones = []
	symbols = []
	if stones.empty():
		for i in numEffects:
			pass
	
	if ownerType == CoreConst.Owner.ItemLibrary:
		pass
	else:
		
		if not wasJustCrafted:
			randEffects()


class RingEffect:
	var triggerType: int
	var stackType: int
	
	func pushEncoded(bitStream) -> void :
		var normalizedStack = stackType - CoreConst.EventType.Lucky
		bitStream.push(triggerType, TriggerType.size())
		bitStream.push(normalizedStack, 16)
		
	
	func setFromEncoded(bitStream):
		triggerType = bitStream.pull(TriggerType.size())
		stackType = bitStream.pull(16) + CoreConst.EventType.Lucky
	


