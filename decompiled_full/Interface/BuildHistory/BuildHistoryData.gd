extends Reference
class_name BuildHistoryData

var id: int
var version: int
var time: int

var classI: int
var loadout: int
var mode: int
var customRules: String
var rating: float
var roundHistory: Array
var skill1Index = null
var skill2Index = null
var subclassIndex = null




func getVersionString() -> String:
	return Game.versionToString(version)

func addRoundData(roundNum: int, result: int, tries: int, 
	health: int, stamina: int, items: String):
	
	var roundData = RoundData.new()
	roundData.result = result
	roundData.tries = tries
	roundData.health = health
	roundData.stamina = stamina
	roundData.items = items
	
	
	if roundHistory.size() < roundNum:
		roundHistory.resize(roundNum)
	
	roundHistory[roundNum - 1] = roundData


func isValid() -> bool:
	for roundI in roundHistory.size():
		if roundHistory[roundI] == null:
			return false
	return true

func getRoundData(roundNum: int):
	if roundNum <= roundHistory.size():
		return roundHistory[roundNum - 1]
	else:
		return null

func getWins(upToRound = getRounds()) -> int:
	var wins: = 0
	for roundI in min(upToRound, roundHistory.size()):
		if roundHistory[roundI].result == Game.RoundResult.Win:
			wins += 1
	return wins

func getLosses(upToRound = getRounds()) -> int:
	var losses: = 0
	for roundI in min(upToRound, roundHistory.size()):
		if roundHistory[roundI].result == Game.RoundResult.Loss:
			losses += 1
	return losses

func getTries(atRound = getRounds()) -> int:
	if roundHistory.empty():
		return Game.MAX_TRIES
	else:
		return roundHistory[atRound - 1].tries

func getSurvivalStartRound() -> int:
	var numWins = 0
	var survivalStartRound = - 1
	for roundI in roundHistory.size():
		if roundHistory[roundI].result == Game.RoundResult.Win:
			numWins += 1
			if numWins == Game.MAX_WINS:
				survivalStartRound = roundI
	
	if roundHistory.size() > survivalStartRound:
		return survivalStartRound
	else:
		return - 1

func getRounds() -> int:
	return roundHistory.size()

func getTimeDif() -> Dictionary:
	var timeDif = Time.get_unix_time_from_system() - time
	var dict = Time.get_time_dict_from_unix_time(timeDif)
	dict["days"] = int(timeDif / (60 * 60 * 24))
	return dict

class RoundData:
	var result: int
	var tries: int
	var health: int
	var stamina: int
	var items: String
