extends Node

const UNRANKED_RATING = - 1000

const RUN_BOARD = "bpb-runs3"
const BETA_BOARD = "bpb-runs1"
const DEMO_BOARD = "bpb-runs1"
const MIN_CACHE_ENTRIES = 30

const OUTDATED_runCachePath = "user://runs.cache"
const OUTDATED_runCachePath_BETA = "user://beta/runs.cache"
const steamCachePath = "user://runs_steam.cache"
const silentwolfCachePath = "user://runs_sw.cache"
const steamCachePath_BETA = "user://beta/runs_steam.cache"
const silentwolfCachePath_BETA = "user://beta/runs_sw.cache"
const steamCachePath_PLAYTEST = "user://playtest/runs_steam.cache"
const silentwolfCachePath_PLAYTEST = "user://playtest/runs_sw.cache"

var steamLeaderboard = null
var lobbies = null

var swSequenceNumber: int = 1
var runsFromCache = []
var silentwolfRuns = []
var gotSwResponse = false

var rounds = []

const DELAY_AFTER_RECEIVE = 20 * 60
var delayAfterRequest: float

var resendTimer
var runsReceivedTime = - INF
var runRequestTime = - INF

var feasibleRuns = []
var curOpponentIndex = 0

var faceDarkReflection: = false

const rematchSameOpponentTimeout = 12
var recentOpponentRuns = []
var recentOpponentNames = []

onready var totalNumGems = BitStream.binaryCeil(ItemBook.getNumGems() + 1)
onready var emptySocketId = totalNumGems - 1



var facedNoConnectionDarkReflection: int

var statisticsMode = false

func getParsedRuns():
	var runs = []
	
	if not silentwolfRuns.empty():
		runs.append_array(silentwolfRuns)
	
	if steamLeaderboard and not steamLeaderboard.parsedRuns.empty():
		runs.append_array(steamLeaderboard.parsedRuns)
	
	if runs.size() < MIN_CACHE_ENTRIES and not runsFromCache.empty():
		runs.append_array(runsFromCache)
	
	return runs

func hasConnected():
	return gotSwResponse or (steamLeaderboard and steamLeaderboard.gotResponse) or Game.EXPO

func _ready() -> void :
	pause_mode = Node.PAUSE_MODE_PROCESS
	
	loadCachedRuns()
	
	var swParams = {
		"game_version": "1.0.0", 
		"log_level": 0, 
		"api_key": "R2h7Ktzvtf2DKnCBs3ImQ1YV0ARb0uIy8SyfXBaS"
	}
	
	if Game.FULLVERSION:
		swParams["game_id"] = "bpb"
	else:
		swParams["game_id"] = "backpackbattles"
	
	SilentWolf.configure(swParams)

	SilentWolf.Scores.connect("sw_scores_received", self, "onSilentwolfRunsReceived")
	
	call_deferred("ready_deferred")

func ready_deferred():
	resendTimer = Timer.new()
	add_child(resendTimer)
	resendTimer.connect("timeout", self, "sendRunRequest")
	
	if SteamHelper.is_init():
		steamLeaderboard = SteamLeaderboard.new()
		add_child(steamLeaderboard)
	
	sendRunRequest()
	
	if runsFromCache.size() < MIN_CACHE_ENTRIES:
		Game.connectingLabel.show()
		resendTimer.start(30)
		delayAfterRequest = 30 - 1
	else:
		
		resendTimer.start(300)
		delayAfterRequest = 300 - 1
	
	if Game.LOBBIES_ENABLED:
		lobbies = load("res://Utility/Lobbies.gd").new()
		add_child(lobbies)
	

func getLeaderboard():
	if Game.DEMO:
		return DEMO_BOARD
	if Game.BETA:
		return BETA_BOARD
	else:
		return RUN_BOARD

func sendRunRequest():
	if Game.EXPO: return
	
	print("runs received ", Util.clockTime - runsReceivedTime, " seconds ago")
	print("runs requested ", Util.clockTime - runRequestTime, " seconds ago")
	
	if (Util.clockTime > runsReceivedTime + DELAY_AFTER_RECEIVE and 
		Util.clockTime > runRequestTime + delayAfterRequest):
		
		print("requesting")
		runRequestTime = Util.clockTime
		
		if steamLeaderboard:
			steamLeaderboard.downloadScores()
			if not Game.BETA and not Game.PLAYTEST:
				
				Util.callDelayed_process(self, "checkSteamRunsReceived", 15)
		
		if not statisticsMode:
			if not steamLeaderboard or Game.BETA or Game.PLAYTEST:
				SilentWolf.Scores.get_high_scores(400, getLeaderboard())
	




func parseSingleScore(score, steam: bool, lobbyMode: bool = false):
	var runData = RunData.new()
	
	var res
	if steam:
		res = runData.fromSteamScore(score, lobbyMode)
	else:
		res = runData.fromSilentWolfScore(score)
	
	if res == RunData.DeserializeResult.VERSION_OK:
		
		
		
		return runData
	else:
		return null


func parseScores(scores):
	var newRuns = []
	
	var largestSequenceNumber = 0
	for score in scores:
		if score.score > largestSequenceNumber:
			largestSequenceNumber = score.score
		var runData = parseSingleScore(score, false)
		if runData:
			newRuns.push_back(runData)
	
	swSequenceNumber = max(swSequenceNumber, largestSequenceNumber + 1)
	return newRuns

func onRunsReceived():
	Game.connectingLabel.hide()
	resendTimer.stop()
	runsReceivedTime = Util.clockTime


func onSilentwolfRunsReceived(_ldName, scores):
	gotSwResponse = true
	silentwolfRuns = parseScores(scores)
	print("received sw: ", silentwolfRuns.size())
	if silentwolfRuns.size() > 0:
		if (silentwolfRuns.size() >= MIN_CACHE_ENTRIES or 
			runsFromCache.size() < MIN_CACHE_ENTRIES):
			cacheRuns(silentwolfRuns, false)
		onRunsReceived()

func checkSteamRunsReceived():
	
	
	if silentwolfRuns.empty() and steamLeaderboard.parsedRuns.empty():
		print("Steam timeout. requesting sw")
		if not statisticsMode:
			SilentWolf.Scores.get_high_scores(400, getLeaderboard())


func onSteamRunsReceived():
	print("received Steam: ", steamLeaderboard.parsedRuns.size())
	if steamLeaderboard.parsedRuns.size() > 0:
		if (steamLeaderboard.parsedRuns.size() >= MIN_CACHE_ENTRIES or 
			runsFromCache.size() < MIN_CACHE_ENTRIES):
			cacheRuns(steamLeaderboard.parsedRuns, true)
		onRunsReceived()
	
	if statisticsMode:
		var statistics = load("res://Utility/Statistics.gd").new()
		add_child(statistics)

func getRunCachePath(steam: bool):
	if Game.EXPO:
		if steam:
			var exePath = OS.get_executable_path()
			var exeDir = exePath.get_base_dir()
			return exeDir + "/runs_steam.cache"
		else:
			return ""
	if Game.PLAYTEST:
		if steam:
			return steamCachePath_PLAYTEST
		else:
			return silentwolfCachePath_PLAYTEST
	elif Game.BETA:
		if steam:
			return steamCachePath_BETA
		else:
			return silentwolfCachePath_BETA
	else:
		if steam:
			return steamCachePath
		else:
			return silentwolfCachePath

func cacheRuns(runs, steam: bool):
	var serializedRuns = []
	for run in runs:
		serializedRuns.push_back(run.serialize())
	
	var err = Util.writeVarToFile(getRunCachePath(steam), serializedRuns)
	if err != OK:
		print("could not cache runs. error: ", err)

func loadCachedRuns():
	
	var dir = Directory.new()
	if Game.BETA:
		dir.remove(OUTDATED_runCachePath_BETA)
	else:
		dir.remove(OUTDATED_runCachePath)
	
	var arguments = {}
	for argument in OS.get_cmdline_args():
		if argument == "-clear_cache":
			print("Clearing cache.")
			return
	
	var cacheFile = File.new()
	var cachedRuns = []
	for source in [false, true]:
		var path = getRunCachePath(source)
		if cacheFile.file_exists(path):
			
			var err = cacheFile.open(path, File.READ)
			if err == OK:
				
				if cacheFile.get_len() > 10:
					var saveData = cacheFile.get_var(true)
					if typeof(saveData) == TYPE_ARRAY:
						for data in saveData:
							if data == null:
								Util.eprint("data == null")
								continue
							var runData = RunData.new()
							var res = runData.fromSerialized(data)
							if res == 0:
								cachedRuns.push_back(runData)
					else:
						print("could not load runs! 1")
				else:
					print("could not load runs! 2")
			else:
				print("could not load runs. error: ", err)
			
			cacheFile.close()
	
	if not cachedRuns.empty():
		
		runsFromCache = cachedRuns
		print("loaded: ", runsFromCache.size())


func startRun():
	rounds.clear()
	facedNoConnectionDarkReflection = 0
	recentOpponentRuns.clear()




func getNextOpponentData(roundReduction: int) -> Dictionary:
	
	
	if Game.curMode == Game.Mode.Lobbies:
		return lobbies.getNextOpponentData()
	
	
	
	if faceDarkReflection:
		
		
		return getDarkReflectionData()
	
	
	
	var opponentRun = null
	
	for i in range(curOpponentIndex, feasibleRuns.size()):
		curOpponentIndex += 1
		var run = feasibleRuns[i]
		var validity = run.isValid(Game.curRound)
		if (validity == RunData.Validity.Ok or 
			(validity == RunData.Validity.TooManyUniques
				and feasibleRuns.size() < 100)):
			opponentRun = run
			break
	
	if not opponentRun:
		return getDarkReflectionData()
	else:
		recentOpponentRuns.push_back(opponentRun)
		recentOpponentNames.push_back(opponentRun.encodedName)
		
		if roundReduction > 0:
			var curRound = opponentRun.deserializeRound(Game.curRound)
			var previousRound = opponentRun.deserializeRound(Game.curRound - roundReduction)
			if previousRound:
				curRound["items"] = previousRound["items"]
			
			
			return curRound
		else:
			
			return opponentRun.deserializeRound(Game.curRound)

func getDarkReflectionData() -> Dictionary:
	var roundData = RunData.deserializeStream(getFallbackOpponent(), Game.VERSION)
	roundData["class"] = Game.PLAYER.getClass()
	roundData["name"] = tr("OPPONENT_PLACEHOLDER")
	roundData["chibi"] = Game.getEffectiveChibiMode()
	var skins = []
	for slot in Game.SkinSlot.size():
		skins.push_back(Game.getSelectedSkin(slot))
	roundData["skins"] = skins
	roundData["reflection"] = true
	return roundData


func notifyOpponentCorrupt():
	if not recentOpponentRuns.empty():
		recentOpponentRuns.pop_back()

func getNumFeasibleRuns() -> int:
	var num = 0
	for run in getParsedRuns():
		if run.getNumRounds() >= Game.curRound:
			num += 1
	return num

func sortOpponents():
	var encodedPlayerName = Util.sharedBitstream.serializeString(Game.getPlayerName())
	feasibleRuns.clear()
	curOpponentIndex = 0
	
	var curRating: = 0
	var weAreUnranked: = false
	
	if Game.curMode == Game.Mode.Unranked:
		if CustomRules.isRankedSwitchMode():
			curRating = Game.getSwitchModeRating()
			weAreUnranked = false
		else:
			var overrideLeague = CustomRules.getLeagueToMatch()
			if overrideLeague == CustomRules.UNRANKED:
				weAreUnranked = true
			else:
				weAreUnranked = false
				curRating = (Game.leagueThresholds[overrideLeague] + Game.leagueThresholds[overrideLeague + 1]) * 0.5
				
	
	elif Game.curMode == Game.Mode.Ranked:
		weAreUnranked = false
		curRating = Game.getRunRating(Game.curClass)
	
	elif Game.curMode == Game.Mode.History:
		if Game.curHistoryData.mode == Game.Mode.Ranked:
			weAreUnranked = false
			curRating = Game.curHistoryData.rating
		elif Game.curHistoryData.mode == Game.Mode.Lobbies:
			weAreUnranked = true
		else:
			var overrideLeague = CustomRules.getLeagueToMatch()
			if overrideLeague == CustomRules.UNRANKED:
				weAreUnranked = true
			else:
				weAreUnranked = false
				
				curRating = (Game.leagueThresholds[overrideLeague] + Game.leagueThresholds[overrideLeague + 1]) * 0.5
	
	var playerResults = Game.getRoundResults()
	
	
	
	
	for run in getParsedRuns():
		if run.getNumRounds() >= Game.curRound:
			feasibleRuns.push_back(run)
	
	feasibleRuns.shuffle()
	



	
	var classCounter
	var maxClasses
	var minClasses
	var inspectClasses = true
	
	if Game.curMode == Game.Mode.Unranked:
		inspectClasses = Util.flip(0.5)
	else:
		inspectClasses = Util.flip(0.8)
	
	if Game.FULLVERSION and inspectClasses:
		classCounter = [0, 0, 0, 0, 0, 0, 0]
		for run in recentOpponentRuns:
			classCounter[run.characterClass] += 1
		
		minClasses = Util.findAll(classCounter, classCounter.min())
		maxClasses = Util.findAll(classCounter, classCounter.max())
		



		
	var recentOpponentNamesDict = Dictionary()
	for i in recentOpponentNames.size():
		recentOpponentNamesDict[recentOpponentNames[i]] = i
	
	var targetWins = playerResults[Game.RoundResult.Win]
	
	if Game.isBelowLeague(Game.Leagues.Master):
		if Util.rng.randf() < 0.5:
			targetWins = max(targetWins - 1, 0)
			
	
	
	
	for run in feasibleRuns:
		run.mmScore = 0.0
		
		
		if run.playerId == Game.getPlayerIdentifier():
			run.mmScore += 10000
		
		elif run.encodedName == encodedPlayerName:
			run.mmScore += 5000
		
		
		var theyAreUnranked = run.rating == UNRANKED_RATING
		if weAreUnranked != theyAreUnranked:
			run.mmScore += 1000
		
		
		var rematchMalus = 0
		
		var matchedBeforeRound = recentOpponentNamesDict.get(run.encodedName, - 1)
		if matchedBeforeRound != - 1:
			var lastEncounter = recentOpponentNames.size() - matchedBeforeRound
			if lastEncounter <= rematchSameOpponentTimeout:
				if lastEncounter < 5:
					rematchMalus += 1100
				else:
					rematchMalus += 131
				rematchMalus += (rematchSameOpponentTimeout - lastEncounter)
			
			elif lastEncounter <= rematchSameOpponentTimeout + 10:
				rematchMalus += 0.2
			elif lastEncounter <= rematchSameOpponentTimeout + 20:
				rematchMalus += 0.1
			
			
		run.mmScore += rematchMalus
		
		
		if Game.FULLVERSION and inspectClasses:
			if run.characterClass in minClasses:
				run.mmScore -= 0.1
			
			if run.characterClass in maxClasses:
				run.mmScore += 0.1
			
			if ( not recentOpponentRuns.empty() and 
				recentOpponentRuns[ - 1].characterClass == run.characterClass):
				run.mmScore += 0.2
				
				if (recentOpponentRuns.size() >= 2 and 
					recentOpponentRuns[ - 2].characterClass == run.characterClass):
					run.mmScore += 22
		
		
		var theirWins = run.getWinsAtRound(Game.curRound - 1)
		var winDif = theirWins - targetWins
		if winDif > 0:
			run.mmScore += 10 * winDif
		else:
			run.mmScore += 5 * abs(winDif)
		
		
		if theirWins == Game.MAX_WINS:
			run.mmScore += 1000
		
		
		if not theyAreUnranked:
			var rankDiff = abs(curRating - run.rating)
			run.mmScore += clamp(rankDiff / 1000.0, 0, 1)
			if rankDiff > 150:
				run.mmScore += 12
			
		
		run.mmScore += Util.rng.randf_range(0, 0.05)
		
		
	
	
	feasibleRuns.sort_custom(Matchmaker, "sort_ascending")
	




	

func getFallbackOpponent() -> BitStream:
	var string = serializeRound()
	var bitStream = BitStream.new()
	bitStream.fromGodotString(string)
	return bitStream
	
func serializeCurrentRound():
	var curRound = serializeRound()
	rounds.push_back(curRound)
	return curRound

func getRoundData(roundNum):
	if rounds.size() < roundNum and Game.EDITOR:
		return rounds[min(roundNum, rounds.size() - 1)]
	return rounds[roundNum]

func serializeRound() -> String:
	var bitStream = BitStream.new()
	
	bitStream.push(Game.PLAYER.getBaseMaxHealth(), Game.MAX_HEALTH)
	bitStream.push(Game.PLAYER.getMaxBaseStamina(), Game.MAX_STAMINA)
	
	var totalNumItems: int
	
	if Util.laterOrEqual(Game.VERSION, "1.1.0"):
		totalNumItems = ItemBook.getNumItems()
	else:
		totalNumItems = 510
	
	for item in Game.PLAYER.INVENTORY.getItems():
		bitStream.push(ItemBook.getItemIndex(item), totalNumItems)
		var topLeft = item.getTopLeftCell()
		bitStream.push(topLeft.x, Game.PLAYER.INVENTORY.MAX_SIZE.x)
		bitStream.push(topLeft.y, Game.PLAYER.INVENTORY.MAX_SIZE.y)
		bitStream.push(item.getFaceDirection(), 4)
		
		
		if item.hasSockets():
			if item.hasGems():
				bitStream.pushBit(true)
				var gems = item.getGems()
				for gem in gems:
					if gem:
						bitStream.push(ItemBook.getGemIndex(gem), totalNumGems)
					else:
						bitStream.push(emptySocketId, totalNumGems)
			else:
				bitStream.pushBit(false)
		
		if item.has_method("getDataPersistent"):
			item.getDataPersistent(bitStream)
		
	return bitStream.toGodotString()

func serializeMetadata() -> BitStream:
	var bitStream = BitStream.new()
	var versionSplit = Game.VERSION.split(".")
	bitStream.push(int(versionSplit[0]), 4)
	bitStream.push(int(versionSplit[1]), 16)
	bitStream.push(int(versionSplit[2]), 64)

	for result in Game.roundResults:
		bitStream.push(result, Game.RoundResult.size())
	
	RunData.serializeCharacterData(bitStream, Game.FULLVERSION)
	
	return bitStream

func pushRun():
	
	
	
	if not Game.canCommitRun:
		return
	
	if facedNoConnectionDarkReflection > 0 and not Game.BETA:
		return
	
	var data = getRunDict()
	var playerName = getPlayerName()
	
	Util.callNextFrame(self, "actuallyPersistRun", [playerName, data])

func getRunDict() -> Dictionary:
	var data = Dictionary()
	data[RunData.VERSION_FIELD] = serializeMetadata().toGodotString()
	
	var rating = Game.getRunRating(Game.curClass)
	if Game.curMode == Game.Mode.Ranked:
		data["r"] = rating
	else:
		data["r"] = UNRANKED_RATING
	
	data["id"] = Game.getPlayerIdentifier()
	
	
	var roundIndex = 0
	for r in rounds:
		data[String(roundIndex)] = r
		roundIndex += 1
	
	return data

func getPlayerName() -> String:
	var playerName = Game.getPlayerName()
	if not Profanity.isGood(playerName):
		playerName = Util.pickRandomElement(replaceNames)
	
	playerName = Util.sharedBitstream.serializeString(playerName)
	return playerName

func actuallyPersistRun(playerName, data: Dictionary):
	var persistToSilentWolf = false
	var persistToSteam = false
	
	if gotSwResponse:
		if steamLeaderboard and steamLeaderboard.gotResponse:
			
			if Util.flip():
				persistToSilentWolf = true
			else:
				persistToSteam = true
		else:
			
			persistToSilentWolf = true
	else:
		if steamLeaderboard and steamLeaderboard.gotResponse:
			
			persistToSteam = true
		
			
	
	var steamSequenceNumber = 0
	if steamLeaderboard:
		steamSequenceNumber = steamLeaderboard.largestSequenceNumber
	
	var sequenceNumber = max(swSequenceNumber, steamSequenceNumber)
	



	




	
	if persistToSilentWolf:
		print("persisting sw")
		
		SilentWolf.Scores.persist_score(playerName, sequenceNumber, 
			getLeaderboard(), data)

	if persistToSteam:
		print("persisting steam")
		
		data["p"] = playerName
		var steamMetaDataString = to_json(data)
		
		
		
		steamLeaderboard.pushScore(steamMetaDataString, sequenceNumber)


const replaceNames = [
	"SifdFan69", 
	"team splattercat", 
	"love wanderbots", 
	"northerlion pog", 
	"siiiiiifd", 
	"retrofan", 
	"tellsplattercat", 
	"the egg", 
	"Skoottie GOAT", 
	"Hi SAG", 
	"2Late4Miracle", 
	"nice try net", 
	"DolphinPhysicist", 
	"Stanz Stan", 
	"AMAZing", 
	"Dogdogdog", 
	"Have Fun Hafu", 
	"Sodapops", 
	"Bahrooooo", 
	"Celery", 
	"Tide of Tim", 
	"Rattatatan", 
	"let him cook", 
	"hi shinji", 
	"Panda in a bag", 
	"Asmodaimond", 
	"buy the game lol", 
	"backpack enjoyer", 
	"gratis151ml", 
	"ede adé", 
	"Maxim Aal", 
	"Grubtor", 
	"It's me Tim", 
	"Hi Mark", 
	"Huge Goobies", 
	"Backpack Bob", 
	"Bob's Backpack", 
	"Backpackcoach", 
	"Bearenstein Hair", 
	"Dan Gooseling", 
	"Raketenbohne", 
	"FootofBlood", 
	"xcuse me", 
	"Threebeers", 
	"Kai Zen", 
	"Rolf"
]

class Matchmaker:
	
	static func sort_ascending(run1: RunData, run2: RunData):
		return run1.mmScore < run2.mmScore

