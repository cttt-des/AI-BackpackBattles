extends Node

const defaultIcon = preload("res://Interface/Lobbies/CustomIcon.png")
const activeIcon = preload("res://Interface/Lobbies/CustomIcon_hovered.png")

const UNRANKED = - 1
const MIN_BONUS_GOLD = - 10
const MAX_BONUS_GOLD = 10
const MAX_BONUS_UNIQUE_CHANCE = 100
const MIN_HP_MULTIPLIER = 20
const MAX_HP_MULTIPLIER = 200

enum Rules{
	LeagueToMatch = 0, 
	BonusGold = 1, 
	BonusTreasures = 2, 
	HealthMultiplier = 3, 
	TreasureLimit = 4, 
	SalesChance = 5, 
	TradeChance = 6, 
	CannotPickBags = 7, 
	SwitchMode = 8
}

enum SwitchModeState{
	Off = 0, 
	Unranked = 1, 
	Ranked = 2
}

const DEFAULTS = {
	Rules.LeagueToMatch: UNRANKED, 
	Rules.BonusGold: 0, 
	Rules.BonusTreasures: 0, 
	Rules.HealthMultiplier: 100, 
	Rules.TreasureLimit: 0, 
	Rules.SalesChance: 0, 
	Rules.TradeChance: 0, 
	Rules.CannotPickBags: false, 
	Rules.SwitchMode: SwitchModeState.Off
}

const MIN = {
	Rules.BonusGold: - 10, 
	Rules.BonusTreasures: 0, 
	Rules.HealthMultiplier: 20, 
	Rules.TreasureLimit: - 1, 
	Rules.SalesChance: - 10, 
	Rules.TradeChance: 0, 
	Rules.SwitchMode: SwitchModeState.Off
}

const MAX = {
	Rules.BonusGold: 10, 
	Rules.BonusTreasures: 100, 
	Rules.HealthMultiplier: 200, 
	Rules.TreasureLimit: 10, 
	Rules.SalesChance: 100, 
	Rules.TradeChance: 100, 
	Rules.SwitchMode: SwitchModeState.Ranked
}

const STEP = {
	Rules.BonusGold: 1, 
	Rules.BonusTreasures: 5, 
	Rules.HealthMultiplier: 5, 
	Rules.TreasureLimit: 1, 
	Rules.SalesChance: 5, 
	Rules.TradeChance: 5, 
	Rules.SwitchMode: 1
}

var customRulesActive: = false

var values: Dictionary





func _init():
	reset()
	

func areCustomRulesActive() -> bool:
	return customRulesActive

func areCustomRulesChanged() -> bool:
	if not customRulesActive:
		return false
	
	for rule in Rules:
		if not isRuleDefault(Rules[rule]):
			return true
	
	return false

func isRuleDefault(rule: int) -> bool:
	return values[rule] == DEFAULTS[rule]

func pushRule(rule: int, bitStream: BitStream):
	var step: int = STEP[rule]
	var encoded: int = getRuleValue(rule) - MIN[rule]
	Util.eassert(encoded % step == 0)
	encoded /= step
	var maxRange = MAX[rule] - MIN[rule]
	Util.eassert(maxRange % step == 0)
	maxRange /= step
	bitStream.push(encoded, maxRange + 1)

func pullRule_noSet(rule: int, bitStream: BitStream):
	var maxRange = MAX[rule] - MIN[rule]
	maxRange /= STEP[rule]
	return bitStream.pull(maxRange + 1) * STEP[rule] + MIN[rule]


func pullRule(rule: int, bitStream: BitStream):
	values[rule] = pullRule_noSet(rule, bitStream)

func serialize() -> String:
	if not customRulesActive:
		return ""
	Util.eprint("Serialize custom rules")
	var bitStream = BitStream.new()
	
	bitStream.push(getLeagueToMatch() + 1, Game.Leagues.size())
	for rule in range(Rules.BonusGold, Rules.TradeChance + 1):
		pushRule(rule, bitStream)
	bitStream.push(getCannotPickBags(), 2)
	
	pushRule(Rules.SwitchMode, bitStream)
	
	
	return bitStream.toGodotString()


func fromString(serialized: String):
	if serialized == "":
		Util.eprint("no custom rules")
		return
	
	var bitStream = BitStream.new()
	bitStream.fromGodotString(serialized)
	
	setLeagueToMatch(bitStream.pull(Game.Leagues.size()) - 1)
	for rule in range(Rules.BonusGold, Rules.TradeChance + 1):
		pullRule(rule, bitStream)
	setCannotPickBags(bitStream.pull(2))
	
	pullRule(Rules.SwitchMode, bitStream)
	
	
	customRulesActive = true


func isSwitchModeNoLoad(serialized: String) -> int:
	var bitStream = BitStream.new()
	bitStream.fromGodotString(serialized)
	
	bitStream.pull(Game.Leagues.size())
	for rule in range(Rules.BonusGold, Rules.TradeChance + 1):
		pullRule_noSet(rule, bitStream)
	bitStream.pull(2)
	
	return pullRule_noSet(Rules.SwitchMode, bitStream)



func reset():
	Util.eprint("Resetting custom rules")
	for rule in Rules.values():
		values[rule] = DEFAULTS[rule]
	customRulesActive = false


func setLeagueToMatch(league):
	values[Rules.LeagueToMatch] = league
	customRulesActive = true
	

func getLeagueToMatch():
	return values[Rules.LeagueToMatch]

func setCannotPickBags(state: bool):
	values[Rules.CannotPickBags] = state
	customRulesActive = true

func getCannotPickBags() -> bool:
	return values[Rules.CannotPickBags]

func setSwitchMode(state: int):
	values[Rules.SwitchMode] = state
	customRulesActive = true

func isSwitchMode() -> bool:
	return values[Rules.SwitchMode] != SwitchModeState.Off

func isRankedSwitchMode() -> bool:
	return values[Rules.SwitchMode] == SwitchModeState.Ranked



func getRuleValue(rule: int):
	return clamp(values[rule], MIN[rule], MAX[rule])

func setRuleValue(rule: int, value: int):
	values[rule] = value
	customRulesActive = true

func setBonusGold(gold):
	setRuleValue(Rules.BonusGold, gold)

func getBonusGold():
	return getRuleValue(Rules.BonusGold)


func setBonusUniqueChance(chance):
	setRuleValue(Rules.BonusTreasures, chance)

func getBonusUniqueChance():
	return getRuleValue(Rules.BonusTreasures)


func setHealthMultiplier(factor):
	setRuleValue(Rules.HealthMultiplier, factor)

func getHealthMultiplier():
	return getRuleValue(Rules.HealthMultiplier)

