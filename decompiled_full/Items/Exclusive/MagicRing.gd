extends Item

onready var numEffects: = int(getP("effects"))
onready var healthThreshold: = getP("healtht") / 100.0
onready var opponentHealthThreshold: = getP("healtht_opp") / 100.0
onready var stones = []
onready var symbols = []

enum TriggerType{
	StartOfBattle = 0, 
	Every = 1, 
	PlayerLow = 2, 
	OppoLow = 3
}

var stackToTypes = {
	Game.EventType.Lucky: Type.Nature, 
	Game.EventType.Spikes: Type.Nature, 
	Game.EventType.Regeneration: Type.Holy, 
	Game.EventType.Heat: Type.Fire, 
	Game.EventType.Vampirism: Type.Vampiric, 
	Game.EventType.Empower: Type.Holy, 
	Game.EventType.Mana: Type.Magic, 
	Game.EventType.Blind: Type.Dark, 
	Game.EventType.Cold: Type.Ice, 
	Game.EventType.Poison: Type.Nature, 
}

var stackToColor = {
	Game.EventType.Lucky: Color(0.329826, 1, 0.263672), 
	Game.EventType.Spikes: Color(0.700867, 1, 0.263672), 
	Game.EventType.Regeneration: Color(1, 0.388672, 0.696724), 
	Game.EventType.Heat: Color(1.1, 0.44, 0.24), 
	Game.EventType.Vampirism: Color(0.900391, 0.04924, 0.04924), 
	Game.EventType.Empower: Color(0.955078, 0.665003, 0.341366), 
	Game.EventType.Mana: Color(0.257812, 0.330292, 1), 
	Game.EventType.Blind: Color(0.569776, 0.196078, 1), 
	Game.EventType.Cold: Color(0.196078, 0.952895, 1), 
	Game.EventType.Poison: Color(0.008865, 0.648438, 0.176254)
}

const triggerTypeSymbols = {
	TriggerType.StartOfBattle: preload("res://Items/Exclusive/Sprites/MagicRing_Symbol2.png"), 
	TriggerType.Every: preload("res://Items/Exclusive/Sprites/MagicRing_Symbol1.png"), 
	TriggerType.PlayerLow: preload("res://Items/Exclusive/Sprites/MagicRing_Symbol3.png"), 
	TriggerType.OppoLow: preload("res://Items/Exclusive/Sprites/MagicRing_Symbol4.png")
}

var effects: Array

var effectDict: Dictionary
var gainedStacks: int
var playerLowTriggered: = false
var oppoLowTriggered: = false
var ringTypes: Array
var textEffect: int

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
	if Game.isBuff(effect.stackType):
		target = character()
	else:
		target = opponent()
	
	var stackName = Game.eventTypeKeys[effect.stackType].to_lower()
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
		stones[effectI].modulate = stackToColor[effect.stackType]
		symbols[effectI].texture = triggerTypeSymbols[effect.triggerType]
		effectI += 1
		
	if not isOnlyForDisplay():
		textEffect = ItemToolTip.TextEffect.None
		
		for effect in effects:
			Util.dictAppend(effectDict, effect.triggerType, effect)
			
			gainedStacks |= 2 << (effect.stackType - Game.EventType.Lucky)
			
			var newType = stackToTypes[effect.stackType]
			if not newType in ringTypes:
				ringTypes.push_back(newType)
			
			if textEffect == ItemToolTip.TextEffect.None and newType in ItemBook.typeToTextEffect:
				textEffect = ItemBook.typeToTextEffect[newType]
		
		if inventory != null:
			inventory.onItemTypeChanged(self)
	else:
		textEffect = ItemToolTip.TextEffect.Gold

func getTypes() -> Array:
	return .getTypes() + ringTypes

func hasType(type: int) -> bool:
	return type in ringTypes or .hasType(type)

func getNumStaticTypes() -> int:
	return .getNumStaticTypes() + ringTypes.size()

func gainsStack(stackType) -> bool:
	return gainedStacks & stackType

func gainsBuffs() -> bool:
	return gainedStacks & Stack.Buff

func inflictsDebuffs() -> bool:
	return gainedStacks & Stack.Debuff

func getTextEffect() -> int:
	return textEffect

func _ready():
	if stones.empty():
		for i in numEffects:
			stones.push_back(sprite.get_node(str("Stone", i + 1)))
			symbols.push_back(sprite.get_node(str("Symbol", i + 1)))
	
	if ownerType == Owner.ItemLibrary:
		Game.itemLibrary.connect("open_library", self, "randEffects")
	else:
		
		if not wasJustCrafted:
			randEffects()

func randEffects(clearIfOnlyDisplay = true):
	effects.clear()
	
	for i in numEffects:
		var effect = RingEffect.new()
		effects.push_back(effect)
		effect.triggerType = Util.rng.randi_range(0, 3)
		effect.stackType = Util.rng.randi_range(Game.EventType.Lucky, 
			Game.EventType.Cold)
		
	
	sortEffects()
	
	if clearIfOnlyDisplay and isOnlyForDisplay():
		effects.clear()

func getScaledParam(stackName: String, paramScale: float) -> float:
	return round(getP(stackName) * paramScale)

func isOnlyForDisplay() -> bool:
	return (ownerType == Owner.ItemLibrary or 
		ownerType == Owner.InfoPanelIcon or 
		ownerType == Owner.Tooltip or 
		ownerType == Owner.RecipeBook or 
		ownerType == Owner.BuildViewerIcon)

func getDescription(wrapInColor = true) -> String:
	var descr: = ""
	
	
	if effects.empty():
		descr += Util.tra("Magic Ring_LIBRARY")
		var effectTemplate: = Util.tra("Magic Ring_LIST")
		
		var params = {}
		for stack in Game.getBuffs() + Game.getDebuffs():
			var stackName = Game.eventTypeKeys[stack].to_lower()
			params[stackName] = getP(stackName)
		
		for triggerI in range(1, 5):
			descr += "\n\n"
			descr += Util.tra(str("Magic Ring_TRIGGER", triggerI))
			
			var paramScale = getP(str("scale", triggerI))
			for stackName in params:
				params[stackName] = Util.highlight(getScaledParam(stackName, paramScale))
			
			var effectStr: = effectTemplate.format(params)
			descr = descr.replace("{effect}", str("\n", effectStr))
		
	else:
		descr += Util.tra("Magic Ring_GENERATED")
		descr += "\n\n"
		
		for effectI in numEffects:
			var effect = effects[effectI]
			descr += Util.tra(str("Magic Ring_TRIGGER", effect.triggerType + 1))
			var effectStr: = ""
			if Game.isBuff(effect.stackType):
				effectStr = Util.tra("Magic Ring_GenericGain")
			else:
				effectStr = Util.tra("Magic Ring_GenericInflict")
			
			
			var stackName = Game.eventTypeKeys[effect.stackType].to_lower()
			var paramScale = getP(str("scale", effect.triggerType + 1))
			effectStr = effectStr.replace("{amount}", Util.highlight(getScaledParam(stackName, paramScale)))
			effectStr = effectStr.replace("{type}", str("$", Game.typeToKeyword(effect.stackType)))
			
			descr = descr.replace("{effect}", str("\n", effectStr))
			if effectI != numEffects - 1:
				descr += "\n\n"
	
	return insertParameters(descr)

func copyFrom(otherRing):
	setData(otherRing.getData())

func getData():
	var bitStream = BitStream.new()
	for effect in effects:
		effect.pushEncoded(bitStream)
	return bitStream.toGodotString()


func setData(_data):
	if _data == null:
		print("no ring data")
		return
	
	effects.clear()
	var bitStream = BitStream.new()
	bitStream.fromGodotString(_data)
	for i in numEffects:
		var effect = RingEffect.new()
		effect.setFromEncoded(bitStream)
		effects.push_back(effect)
	
	sortEffects()

func persistDataInShop() -> bool:
	return true

func getDataPersistent(bitStream: BitStream):
	for effect in effects:
		effect.pushEncoded(bitStream)




func getDataPersistentBits():
	return numEffects * (2 + 4)


func onCraftedFrom(baseItem, ingredients):
	effects.clear()
	effects.append_array(baseItem.effects)
	effects.append_array(ingredients[0].effects)
	
	
	effects.remove(Util.rng.randi_range(0, 3))
	
	sortEffects()

class RingEffect:
	var triggerType: int
	var stackType: int
	
	func pushEncoded(bitStream: BitStream) -> void :
		var normalizedStack = stackType - Game.EventType.Lucky
		bitStream.push(triggerType, TriggerType.size())
		bitStream.push(normalizedStack, 16)
		
	
	func setFromEncoded(bitStream: BitStream):
		triggerType = bitStream.pull(TriggerType.size())
		stackType = bitStream.pull(16) + Game.EventType.Lucky
	



