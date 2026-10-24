extends Reference
class_name OpponentPoolAdapter

const MAX_DISPLAY_TRIES: = 5

var runData: RunData
var id: int

var classI: int setget , get_classI
var loadout: int setget , get_loadout
var mode: int setget , get_mode
var customRules: String = ""
var rating: float setget , get_rating

var startingBagIndex = null
var subclassIndex = null
var skill1Index = null
var skill2Index = null
var specialItemsLoaded: bool = false

func _init(_runData: RunData, _id: int):
	runData = _runData
	id = _id

func get_classI() -> int:
	return runData.characterClass

func get_loadout() -> int:
	return runData.loadout

func get_mode() -> int:
	if runData.rating == - 1000:
		return Game.Mode.Unranked
	return Game.Mode.Ranked

func get_rating() -> float:
	return runData.rating

func getVersionString() -> String:
	return runData.entryVersion

func getRounds() -> int:
	return runData.getNumRounds()

func getRoundData(roundNum: int):
	if roundNum < 1 or roundNum > runData.getNumRounds():
		return null

	var roundData = RoundData.new()
	roundData.items = runData.rounds[roundNum - 1]

	var fullData = runData.deserializeRound(roundNum)
	if fullData:
		roundData.health = int(fullData.get("health", Game.getMaxHealthInRound(runData.characterClass, roundNum)))
		roundData.stamina = int(fullData.get("stamina", Game.classResources[runData.characterClass].stamina))

	if roundNum - 1 < runData.results.size():
		roundData.result = runData.results[roundNum - 1]
	else:
		roundData.result = Game.RoundResult.RunOver

	roundData.tries = getTries(roundNum)
	return roundData

func getWins(upToRound = getRounds()) -> int:
	return runData.getWinsAtRound(upToRound)

func getLosses(upToRound = getRounds()) -> int:
	return upToRound - getWins(upToRound)

func getTries(atRound = getRounds()) -> int:
	var tries = min(Game.MAX_TRIES, MAX_DISPLAY_TRIES)
	var wins = 0
	var survivalGranted = false
	for roundI in min(atRound, runData.results.size()):
		var roundNum = roundI + 1
		var result = runData.results[roundI]
		if result == Game.RoundResult.Win:
			wins += 1
		elif result == Game.RoundResult.Loss:
			tries -= 1

		if roundNum == Game.SUBCLASS_ROUND and tries > 0 and tries < Game.MAX_TRIES:
			tries = min(tries + 1, MAX_DISPLAY_TRIES)

		if not survivalGranted and wins >= Game.MAX_WINS:
			tries = min(tries + 1, MAX_DISPLAY_TRIES)
			survivalGranted = true

	return int(clamp(tries, 0, MAX_DISPLAY_TRIES))

func isValid() -> bool:
	return runData.getNumRounds() > 0

func getTimeDif() -> Dictionary:
	return {}

func getPlayerName() -> String:
	return runData.getDecodedName()

func getPlayerId() -> String:
	return runData.playerId

func getCharacterClass() -> int:
	return runData.characterClass

func getLoadout() -> int:
	return runData.loadout

func getRating() -> float:
	return runData.rating

func loadSpecialItems():
	if specialItemsLoaded:
		return
	specialItemsLoaded = true

	if runData.getNumRounds() >= 1:
		var roundData = runData.deserializeRound(1)
		if roundData and roundData.has("items"):
			for itemData in roundData["items"]:
				var descriptor = itemData["d"] if itemData.has("d") else null
				if descriptor and descriptor.isBag() and descriptor.rarity == Item.Rarity.Unique:
					startingBagIndex = descriptor.itemIndex
					break

	if runData.getNumRounds() >= Game.SUBCLASS_ROUND:
		var roundData2 = runData.deserializeRound(Game.SUBCLASS_ROUND)
		if roundData2 and roundData2.has("items"):
			for itemData2 in roundData2["items"]:
				var descriptor2 = itemData2["d"] if itemData2.has("d") else null
				if descriptor2 and descriptor2.isSubclassItem():
					subclassIndex = descriptor2.itemIndex
					break

	if runData.getNumRounds() >= Game.SKILL_ROUND1:
		skill1Index = findSkillInRound(Game.SKILL_ROUND1)
	if runData.getNumRounds() >= Game.SKILL_ROUND2:
		skill2Index = findSkillInRound(Game.SKILL_ROUND2)

func findSkillInRound(roundNum: int):
	if roundNum <= 1:
		return null

	var currentRound = runData.deserializeRound(roundNum)
	var previousRound = runData.deserializeRound(roundNum - 1)
	if not currentRound or not previousRound:
		return null
	if not currentRound.has("items") or not previousRound.has("items"):
		return null

	var previousItems = {}
	for itemData in previousRound["items"]:
		var descriptor = itemData["d"] if itemData.has("d") else null
		if descriptor:
			previousItems[descriptor.itemIndex] = true

	for itemData2 in currentRound["items"]:
		var descriptor2 = itemData2["d"] if itemData2.has("d") else null
		if descriptor2 and not previousItems.has(descriptor2.itemIndex):
			if Item.Type.Skill in descriptor2.types:
				return descriptor2.itemIndex

	return null

func getStartingBagIndex():
	loadSpecialItems()
	return startingBagIndex

func getSubclassIndex():
	loadSpecialItems()
	return subclassIndex

func getSkill1Index():
	loadSpecialItems()
	return skill1Index

func getSkill2Index():
	loadSpecialItems()
	return skill2Index

func getOverallValidity():
	if runData.getNumRounds() <= 0:
		return RunData.Validity.Invalid

	var details = getValidityDetails()
	if details["invalid"] > 0:
		return RunData.Validity.Invalid

	var questionableRate = 0.0
	if details["total"] > 0:
		questionableRate = details["questionable"] / float(details["total"])
	if questionableRate > 0.3:
		return RunData.Validity.Invalid

	if details["questionable"] > 0:
		return RunData.Validity.Questionable
	if details["too_many_uniques"] > 0:
		return RunData.Validity.TooManyUniques

	return RunData.Validity.Ok

func getRoundValidity(roundNum: int):
	if roundNum < 1 or roundNum > runData.getNumRounds():
		return RunData.Validity.Invalid

	var currentRound = max(runData.getNumRounds(), roundNum)
	var validity = runData.isRoundValid(roundNum, currentRound)

	if validity == RunData.Validity.Invalid and currentRound > roundNum:
		var directRoundValidity = runData.isRoundValid(roundNum, roundNum)
		if directRoundValidity == RunData.Validity.Questionable:
			return RunData.Validity.Questionable

	return validity

func getValidityDetails() -> Dictionary:
	var details = {
		"total": runData.getNumRounds(), 
		"ok": 0, 
		"questionable": 0, 
		"invalid": 0, 
		"too_many_uniques": 0, 
		"problem_rounds": [], 
		"round_statuses": []
	}
	for i in range(1, runData.getNumRounds() + 1):
		var validity = getRoundValidity(i)
		match validity:
			RunData.Validity.Ok:
				details["ok"] += 1
			RunData.Validity.Questionable:
				details["questionable"] += 1
				details["problem_rounds"].append(i)
			RunData.Validity.Invalid:
				details["invalid"] += 1
				details["problem_rounds"].append(i)
			RunData.Validity.TooManyUniques:
				details["too_many_uniques"] += 1
				details["problem_rounds"].append(i)
		if validity != RunData.Validity.Ok:
			details["round_statuses"].append("%d: %s" % [i, str(validity)])
	return details

class RoundData:
	var items: String
	var health: int
	var stamina: int
	var result: int
	var tries: int
