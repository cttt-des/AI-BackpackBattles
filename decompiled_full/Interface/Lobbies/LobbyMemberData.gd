extends Reference
class_name LobbyMemberData

signal ready
signal data_changed
signal round_received

var lastMetadata: String
var steamId: int
var playerName: String
var ugcId: int
var characterClass: int
var loadout: int
var chibi: bool
var skins: Array

var readyForCombat: bool
var roundResults: Array
var triesLeft: Array
var roundData: Array
var fightsFinished: int
var curRanking: int

func _init(_steamId: int, _ugcId: int):
	steamId = _steamId
	ugcId = _ugcId
	roundResults.resize(Game.MAX_ROUNDS_LOBBIES)
	roundResults.fill(Game.RoundResult.RunOver)
	roundData.resize(Game.MAX_ROUNDS_LOBBIES)
	triesLeft.resize(Game.MAX_ROUNDS_LOBBIES)
	triesLeft[0] = Game.MAX_TRIES_LOBBIES
	fightsFinished = 0
	readyForCombat = false

func setData(_playerName: String, _class: int, _loadout: int, 
	_chibi: bool, _skins: Array):
	
	playerName = _playerName
	characterClass = _class
	loadout = _loadout
	chibi = _chibi
	skins = _skins
	
	emit_signal("data_changed")

func isSelf() -> bool:
		return SteamHelper.STEAM_ID == steamId

func isReady() -> bool:
	return readyForCombat

func setReady(ready: bool):
	readyForCombat = ready
	if readyForCombat:
		emit_signal("ready")


func addRoundData(forRound: int, _roundData: String):
	roundData[forRound - 1] = _roundData
	
	emit_signal("round_received", forRound)






func getRoundData(forRound) -> String:
	return roundData[forRound - 1]

func getWinsAtRound(roundNum: int) -> int:
	var wins = 0
	for roundI in roundNum:
		if roundResults[roundI] == Game.RoundResult.Win:
			wins += 1
	return wins

func getCurrentWins() -> int:
	return getWinsAtRound(fightsFinished)


func getTriesAtRound(roundNum: int) -> int:
	if roundNum == 0:
		return Game.MAX_TRIES_LOBBIES
	return triesLeft[roundNum - 1]

func getCurrentTries() -> int:
	return getTriesAtRound(fightsFinished)

func getLossesAtRound(roundNum: int) -> int:
	var losses = 0
	for roundI in roundNum:
		if roundResults[roundI] == Game.RoundResult.Loss:
			losses += 1
	return losses

func getCurrentLosses() -> int:
	return getLossesAtRound(fightsFinished)

func getResultOfRound(roundNum: int) -> int:
	return roundResults[roundNum - 1]

func getLastResult() -> int:
	return roundResults[fightsFinished - 1]

func getCurrentScore() -> int:
	return getCurrentWins()









func setResultsFromString(results: String):
	
	fightsFinished = 0
	var tries = Game.MAX_TRIES_LOBBIES
	
	for roundI in results.length():
		var result = int(results[roundI])
		roundResults[roundI] = result
		
		if result != Game.RoundResult.RunOver:
			fightsFinished += 1
			
			if result == Game.RoundResult.Win:
				triesLeft[roundI] = tries
			elif result == Game.RoundResult.Loss:
				triesLeft[roundI] = max(0, tries - 1)
			tries = triesLeft[roundI]












