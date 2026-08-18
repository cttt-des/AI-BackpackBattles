extends Node

signal lobby_created
signal lobby_closed
signal lobby_left
signal lobby_joined
signal lobby_join_confirmed
signal join_result
signal lobby_join_failed
signal config_changed
signal member_added
signal member_removed
signal kicked
signal found_opponent
signal score_changed
signal start_countdown
signal update_ready_counter
signal lobby_results
signal all_end_results_received

enum JoinResult{
	Confirmed, 
	Unconfirmed, 
	Restricted_AlreadyStarted, 
	Restricted_HostLeft, 
	Restricted_Banned, 
	Error_CodeInvalid, 
	Error_VersionMismatch
}

enum ResponseCode{
	Ok = 0, 
	AlreadyStarted = 1, 
	MemberLimitReached = 2, 
	ManualKick = 3
}

enum PartyState{
	NoParty, 
	Hosting, 
	Connecting, 
	Connected, 
	Reconnecting
}










enum MessageType{
	Member_Joined = 0, 
	Member_Left = 1, 
	Member_Reconnected = 2, 
	Member_RoundData = 3, 
	Member_RoundResult = 4, 
	Host_GameStart = 5, 
	Host_Time = 6, 
	Host_CombatStart = 7, 
	Host_Kicked_Member = 8
	
}



enum LobbyJoinedResult{
	SUCCESS = 1, 
	DOESNT_EXIST = 2, 
	NOT_ALLOWED = 3, 
	FULL = 4, 
	ERROR = 5, 
	BANNED = 6, 
	LIMITED = 7, 
	CLAN_DISABLED = 8, 
	COMMUNITY_BAN = 9, 
	MEMBER_BLOCKED_YOU = 10, 
	YOU_BLOCKED_MEMBER = 11
	RATE_LIMITED = 15
}


enum ChatEntryType{
	ChatMsg = 1, 
	Typing = 2, 
	InviteGame = 3, 
	Emote = 4, 
	LeftConversation = 6, 
	Entered = 7, 
	WasKicked = 8, 
	WasBanned = 9, 
	Disconnected = 10, 
	HistoricalChat = 11, 
	LinkBlocked = 14
}

enum ChatMemberChange{
	Joined = 1, 
	Left = 2, 
	Disconnected = 4, 
	Kicked = 8, 
	Banned = 10
}

enum MatchMaking{
	Random, 
	Elimination, 
	RoundRobin, 
	EvenStats, 
	Strongest, 
	PrioritizeHost = 16
}

const scoreboardScene = preload("res://Interface/Lobbies/LobbyScoreboard.tscn")
const scoreboardButtonScene = preload("res://Interface/Lobbies/ScoreboardButton.tscn")
const lobbyTimerScene = preload("res://Interface/Lobbies/LobbyTimer.tscn")
const roundDurationCurve = preload("res://Interface/Lobbies/RoundDuration.tres")
const COMBAT_TIME: = 20.0
const STARTGAME_COUNTDOWN: = 3.0
const MIN_MEMBERS: = 2
const MAX_MEMBERS: = 99
const USE_MEMBER_UGC: = false
const READ_MEMBER_UGC: = false
const retryTime = 10.0
const DELAY_COMPENSATION = 0.2
const memberInfoKey = "A"
const speedConfigKey = "B"
const sizeConfigKey = "C"
const customRulesConfigKey = "D"
const matchingConfigKey = "E"
const nextFightTimeKey = "F"

const resultsKey = "G"
const sqnKey = "H"
const membersKey = "I"
const membersSqnKey = "J"
const READY = "K"
const hostUgcFields = ["id", "lobbyId", "v"]
var symbolToNumber: Dictionary


var curLobbyId: int
var curPartyUgcId: int
var memberUgcItem = null
var ugcItem = null
var memberUgcId: int
var members: Array
var memberData: Dictionary
var memberList: Array
var partyState: int
var hostSteamId: int
var reconnecting: bool
var liveReconnecting: bool
var joinConfirmed: bool
var gameHasStarted: bool
var onResultsScreen: bool
var ignoreLobbyUpdates: bool
var lastFightTimestamp: String
var feasibleRuns: Array
var opponentHistory: Array
var hostUgcQueryHandle: int
var partyUgcMetadata: Dictionary
var metadataSqn: int
var memberMetadataSqn: int
var opponentRuns: Array
var opponentQueryHandle = 0


var H_hostUgcId: int
var H_hostUgcMetadata: Dictionary



var lobbyTimer = null
var scoreboardButton = null
var scoreboardNode = null
var scoreboard = null



var lobbySize: = 20
var lobbySpeed = SpeedLevel.Normal
var customRules: String
var matchMaking: int = MatchMaking.Random
var prioritizeHost: bool

enum SpeedLevel{
	Slowest = 1, 
	Slower = 2, 
	Slow = 3, 
	Normal = 4, 
	Fast = 5, 
	Faster = 6, 
	Fastest = 7
}


var speedFactors = {
	SpeedLevel.Slowest: 4.0, 
	SpeedLevel.Slower: 2.5, 
	
	SpeedLevel.Slow: 1.5, 
	SpeedLevel.Normal: 1.0, 
	SpeedLevel.Fast: 0.75, 
	SpeedLevel.Faster: 0.5, 
	SpeedLevel.Fastest: 0.3
	
}


func _ready():
	pause_mode = Node.PAUSE_MODE_PROCESS
	
	Steam.connect("ugc_query_completed", self, "onOpponentQueryCompleted")
	Steam.connect("ugc_query_completed", self, "onHostUgcQueryCompleted")
	
	Steam.connect("lobby_created", self, "onLobbyCreated")
	Steam.connect("lobby_joined", self, "onLobbyJoined")
	Steam.connect("lobby_chat_update", self, "onLobbyChatUpdate")
	Steam.connect("lobby_message", self, "chatMessageReceived")
	Steam.connect("lobby_data_update", self, "onLobbyDataUpdate")
	
	Game.connect("character_changed", self, "onOwnClassChanged")
	Game.connect("random_character_changed", self, "onOwnClassChanged")
	Game.connect("fresh_run_started", self, "onGameStart")
	Game.connect("combat_end", self, "onFightFinished")
	
	for i in symbols.size():
		symbolToNumber[symbols[i]] = i
	
	resetState()
	






const symbolSize = 5
const numSymbols = int(ceil(64.0 / symbolSize))
const mod = int(pow(2, symbolSize))
const baseValue = 3550000000


func idToString(id: int) -> String:
	
	var string = ""
	id -= baseValue
	if id < 0:
		string = "-"
		id = abs(id)
	for i in numSymbols:
		var symbolIndex = id % mod
		string = symbols[symbolIndex] + string
		id = id >> symbolSize
	
	
	for i in numSymbols:
		string = string.trim_prefix(symbols[0])
	
	return string

func idFromString(idAsString: String):
	var id = 0
	var isNegative = false
	
	if idAsString.ends_with("-"):
		idAsString = idAsString.trim_suffix("-")
		isNegative = true
	
	var missing = numSymbols - idAsString.length()
	idAsString = symbols[0].repeat(missing) + idAsString
	
	for i in numSymbols:
		var symbolIndex = symbolToNumber[idAsString[i]]
		var add = symbolIndex << ((numSymbols - i - 1) * symbolSize)
		id += add
	
	if isNegative:
		id = baseValue - id
	else:
		id += baseValue
	
	return id

func isInLobby() -> bool:
	return curLobbyId != 0

func isActiveMember() -> bool:
	return partyState == PartyState.Connected or partyState == PartyState.Hosting

func getNumMembers() -> int:
	return memberData.size()

func isMemberHost(memberSteamId) -> bool:
	return hostSteamId == memberSteamId

func isMe(id) -> bool:
	return id == SteamHelper.STEAM_ID

func isHost() -> bool:
	return hostSteamId == SteamHelper.STEAM_ID

func isClient() -> bool:
	return not isHost()

func setReady():
	getOwnMemberData().setReady(true)
	setLobbyMemberData(str(Game.curRound), READY)
	emit_signal("update_ready_counter")
	checkAllReady()

func prepareCombat():
	
	
	var curRoundMetadata = RunDatabase.serializeCurrentRound()
	if isActiveMember():
		getOwnMemberData().setReady(false)
		getOwnMemberData().addRoundData(Game.curRound, curRoundMetadata)
		
		
		setLobbyMemberData(str(Game.curRound), curRoundMetadata)
		
		pushRoundToUgc()
		checkEnterCombat()


func startCombat():
	
	reconnecting = false
	if isHost():
		setRoundAndTimeMetadata(Game.curRound)

func setRoundAndTimeMetadata(roundI):
	print("setting time metadata")
	var roundDur = getRoundDuration(roundI)
	if roundI == 0:
		roundDur += STARTGAME_COUNTDOWN
	var nextFightTime = lobbyTimer.getCurTime() + roundDur
	var timeString = String(lobbyTimer.getCurTime()) + MSG_DELIMITER + String(roundDur)
	setLobbyData_sqn(nextFightTimeKey, timeString)
	
	
	lobbyTimer.updateTimer(nextFightTime)

func setMemberListMetadata():
	var string = ""
	for i in memberList.size():
		string += str(memberList[i])
		if i != memberList.size() - 1:
			string += MSG_DELIMITER
	
	setLobbyData_sqn(membersKey, string, membersSqnKey)

func getPlayerMetadata() -> String:
	var data = RunDatabase.getRunDict()
	data["p"] = RunDatabase.getPlayerName()
	var steamMetaDataString = to_json(data)
	return steamMetaDataString

func pushRoundToUgc():
	if not USE_MEMBER_UGC: return
	
	print("updating ugc with round data")
	var metaDataString = getPlayerMetadata()
	memberUgcItem = UGCItem.new(metaDataString, memberUgcId)
	memberUgcItem.connect("item_updated", self, "onUgcUpdated")
	add_child(memberUgcItem)
	if memberUgcId != 0:
		memberUgcItem.update()

func onUgcUpdated():
	if not READ_MEMBER_UGC: return
	
	print("Round pushed!")
	
	
	if isHost():
		findOpponents()
	else:
		requestHostUgc()

func findOpponents():
	print("querying for opponents... ", members.size())
	var matchmakingOpponents = []
	for member in members:
		if member != memberUgcId:
			matchmakingOpponents.push_back(member)
	opponentQueryHandle = Steam.createQueryUGCDetailsRequest(matchmakingOpponents)
	Steam.setReturnMetadata(opponentQueryHandle, true)
	Steam.sendQueryUGCRequest(opponentQueryHandle)

func onOpponentQueryCompleted(handle, result, results_returned, 
	total_matching, cached: bool):
	
	if handle != opponentQueryHandle: return
	
	opponentRuns.clear()
	
	print(Util.time, " opponent query result: ", result, ", num results: ", results_returned, " total_matching: ", total_matching)
	
	if results_returned > 0:
		RunDatabase.steamLeaderboard.parseMetadata(handle, results_returned, 
			opponentRuns, true)
	
	print("#parsed opponents: ", opponentRuns.size())
	
	Steam.releaseQueryUGCRequest(handle)
	opponentQueryHandle = 0
	
	
	feasibleRuns.clear()
	for run in opponentRuns:
		if run.getNumRounds() >= Game.curRound:
			feasibleRuns.push_back(run)
	
	print("opponents with enough rounds: ", feasibleRuns.size())
	
	if opponentRuns.size() > 0 and feasibleRuns.size() > 0:
		emit_signal("found_opponent")
	else:
		print("retrying in ", retryTime)
		Util.callDelayed_process(self, "findOpponents", retryTime)


func getNextOpponentData() -> Dictionary:
	if isActiveMember():
		var data: LobbyMemberData = pickOpponent()
		if data == null:
			return RunDatabase.getDarkReflectionData()
		else:
			opponentHistory.push_back(data.steamId)
			
			return RunData.createRoundDict(data.getRoundData(Game.curRound), 
				data.characterClass, data.loadout, data.playerName, data.chibi, 
				data.skins, Game.VERSION, false)
	else:
		return Util.pickRandomElement(feasibleRuns).deserializeRound(Game.curRound)

func createParty():
	createLobby()

func createLobby():
	ignoreLobbyUpdates = false
	hostSteamId = SteamHelper.STEAM_ID
	print("Trying to create lobby.")
	
	Steam.createLobby(3, MAX_MEMBERS + 20)
	




func getVersionString() -> String:
	var version = Game.VERSION + Game.SUBVERSION
	if Game.BETA:
		version += "BETA"
	return version

func onLobbyCreated(result, lobbyId):
	if result == 1:
		print("lobby created! id: ", lobbyId)
		curLobbyId = lobbyId
		H_hostUgcMetadata["v"] = getVersionString()
		H_hostUgcMetadata["lobbyId"] = str(curLobbyId)
		if USE_MEMBER_UGC:
			createMemberUgc()
		else:
			finishJoining()
		
		setConfigDefault_Host()
	else:
		print("could not create lobby")

func createMemberUgc():
	var metadataString = getPlayerMetadata()
	ugcItem = UGCItem.new(metadataString)
	ugcItem.connect("item_updated", self, "onMemberUgcCreated")
	add_child(ugcItem)

func onMemberUgcCreated():
	print("Member ugc created!")
	memberUgcId = ugcItem.get_id()
	ugcItem = null
	if isHost():
		members.push_back(memberUgcId)
		H_hostUgcMetadata["members"] = members
		
	finishJoining()

func finishJoining():
	if isHost():
		H_hostUgcMetadata["id"] = str(SteamHelper.STEAM_ID)
		createHostUgc()
	else:
		joinLobby(partyUgcMetadata["lobbyId"])
		hostSteamId = int(partyUgcMetadata["id"])
	
func createHostUgc():
	var metadataStr = to_json(H_hostUgcMetadata)
	
	ugcItem = UGCItem.new(metadataStr)
	ugcItem.connect("item_updated", self, "onHostUgcCreated")
	ugcItem.connect("item_creation_failed", self, "onHostUgcCreationFailed")
	add_child(ugcItem)
	

func onHostUgcCreated():
	H_hostUgcId = ugcItem.get_id()
	ugcItem = null
	partyState = PartyState.Hosting
	print("Lobby creation 2/2")
	emit_signal("lobby_created", idToString(H_hostUgcId))

func onHostUgcCreationFailed():
	print("Lobby creation failed")
	
	



func joinParty(lobbyCode: String):
	ignoreLobbyUpdates = false
	print("Trying to join lobby as member ", lobbyCode)
	partyState = PartyState.Connecting
	curPartyUgcId = idFromString(lobbyCode)
	requestHostUgc()

func getHostId() -> int:
	return hostSteamId

func getHostUgcId() -> int:
	return curPartyUgcId

func getLobbyId() -> int:
	return curLobbyId

func requestHostUgc():
	hostUgcQueryHandle = Steam.createQueryUGCDetailsRequest([curPartyUgcId])
	Steam.setReturnMetadata(hostUgcQueryHandle, true)
	Steam.sendQueryUGCRequest(hostUgcQueryHandle)


func onInvalidCode():
	Util.showPopupMessage("STATUS_Invalid")
	emit_signal("join_result", JoinResult.Error_CodeInvalid)
	releaseQuery()

func onHostUgcQueryCompleted(handle, result, results_returned, 
	total_matching, cached: bool):
	
	if handle != hostUgcQueryHandle: return
	
	print("Lobby query finished ", result)
	
	if result == 1 and results_returned > 0:
		var metadata = Steam.getQueryUGCMetadata(handle, 0)
		
		if metadata.length() < 20:
			onInvalidCode()
			return
		
		var jsonResult = JSON.parse(metadata)
		if jsonResult.error != OK or typeof(jsonResult.result) != TYPE_DICTIONARY:
			onInvalidCode()
			return
		
		for field in hostUgcFields:
			if not jsonResult.result.has(field):
				onInvalidCode()
				return
		
		var hostVersion = jsonResult.result["v"]
		if getVersionString() != hostVersion:
			Util.showPopupMessage("ERROR_VersionMismatch", {"version": hostVersion})
			emit_signal("join_result", JoinResult.Error_VersionMismatch)
			releaseQuery()
			return
		
		partyUgcMetadata = jsonResult.result
		
		
		
		
		
		if partyUgcMetadata.get("started", false):
			
			Util.showPopupMessage("ERROR_JoinPhaseOver")
			emit_signal("join_result", JoinResult.Restricted_AlreadyStarted)
			releaseQuery()
			return
		
		if USE_MEMBER_UGC:
			members = partyUgcMetadata["members"].duplicate()
		
		if partyState == PartyState.Connecting:
			print("Lobby found!")
			if USE_MEMBER_UGC:
				createMemberUgc()
			else:
				finishJoining()
		
		elif partyState == PartyState.Connected:
			if USE_MEMBER_UGC:
				if memberUgcId in members:
					
					members.erase(memberUgcId)
					
			
			if READ_MEMBER_UGC:
				findOpponents()
		
		
	else:
		print("error when fetching party")
		
	
	releaseQuery()

func releaseQuery():
	Steam.releaseQueryUGCRequest(hostUgcQueryHandle)
	hostUgcQueryHandle = 0

func joinLobby(lobbyId):
	print("Trying to join lobby")
	Steam.joinLobby(int(lobbyId))


func onLobbyJoined(lobbyId, _permissions, locked, response):
	print("Lobby joined ", response)
	
	var result
	if response == LobbyJoinedResult.SUCCESS:
		result = JoinResult.Unconfirmed
	elif response == LobbyJoinedResult.DOESNT_EXIST:
		result = JoinResult.Restricted_HostLeft
	elif (response == LobbyJoinedResult.BANNED or 
		response == LobbyJoinedResult.COMMUNITY_BAN):
		result = JoinResult.Restricted_Banned
	
	emit_signal("join_result", result)
	
	
	if response != LobbyJoinedResult.SUCCESS:
		onJoinFailed()
		emit_signal("lobby_join_failed")
		return
	
	curLobbyId = lobbyId
	
	
	
	if reconnecting:
		updateOwnMetadata()
		onMemberListChanged()
		if not SteamHelper.STEAM_ID in memberData:
			
			onJoinFailed()
			emit_signal("lobby_join_failed")
			return
	
	liveReconnecting = false
	
	emit_signal("lobby_joined")
	
	
	
	if reconnecting:
		ensureTimer()
		ensureScoreboard()
		gameHasStarted = true
		collectRoundData()
		
		
		
		if isHost():
			partyState = PartyState.Hosting
			metadataSqn = int(getLobbyData(sqnKey, false))
			memberMetadataSqn = int(getLobbyData(membersSqnKey, false))
			
			onConfigUpdated()
			onGameDataUpdated()
		else:
			partyState = PartyState.Connected
			
		
	else:
		
		updateOwnMetadata()
		
		if isHost():
			print("Lobby creation 1/2")
			addMember_Host(SteamHelper.STEAM_ID)
		else:
			partyState = PartyState.Connected
			
			

func onJoinFailed():
	if liveReconnecting:
		print("Could not reconnect after disconnect.")
		onLobbyClosed()
	else:
		Steam.leaveLobby(curLobbyId)
		resetState()

func resetState():
	reconnecting = false
	liveReconnecting = false
	joinConfirmed = false
	gameHasStarted = false
	onResultsScreen = false
	partyState = PartyState.NoParty
	
	curLobbyId = 0
	hostSteamId = 0
	hostUgcQueryHandle = 0
	curPartyUgcId = 0
	H_hostUgcId = 0
	
	members.clear()
	memberData.clear()
	partyUgcMetadata.clear()
	memberList.clear()
	feasibleRuns.clear()
	opponentHistory.clear()
	H_hostUgcMetadata.clear()

	metadataSqn = - 1
	memberMetadataSqn = - 1
	customRules = ""
	matchMaking = MatchMaking.Random
	prioritizeHost = false
	lastFightTimestamp = ""


func leaveLobby():
	if not isInLobby(): return
	
	print("Leaving Lobby.")
	
	if not onResultsScreen:
		sendLeaveMessage()
	
	Steam.leaveLobby(curLobbyId)
	
	ignoreLobbyUpdates = true
	resetState()
	
	if lobbyTimer != null:
		lobbyTimer.disable()
		lobbyTimer = null
	if scoreboard != null:
		deleteScoreboard()
	
	emit_signal("lobby_left")


func onLobbyChatUpdate(lobbyId, changedId, makingChangeId, chatState):
	
	if Game.EDITOR:
		print("Lobby change - changedId: ", changedId, " makingChange: ", makingChangeId, 
		" chatState: ", Util.enumToString(ChatMemberChange, chatState))
	
	if isMe(changedId):
		if chatState == ChatMemberChange.Disconnected:
			
			
			print("trying to reconnect after disconnect")
			reconnecting = true
			liveReconnecting = true
			partyState = PartyState.Reconnecting
			joinLobby(curLobbyId)
			
			
	
	
	
	elif isMemberHost(changedId):
		if chatState == ChatMemberChange.Joined:
			
			makeHostOwner()
		else:
			
			if not gameHasStarted:
				onLobbyClosed()

func sendChatMessage(message: String):
	print("Sending msg to lobby: ", message, " type: ", Util.enumToString(MessageType, int(message[0])))
	Steam.sendLobbyChatMsg(curLobbyId, message)

func chatMessageReceived(lobbyId: int, memberId: int, buffer: String, chatType: int):
	
	if ignoreLobbyUpdates: return
	if memberId == SteamHelper.STEAM_ID:
		
		return
	
	
	
	if chatType == ChatEntryType.ChatMsg:
		var split = buffer.split(MSG_DELIMITER)
		
		var type = int(split[0])
		print("Message type: ", Util.enumToString(MessageType, type))
		
		match type:









					
			MessageType.Member_Left:
				if memberId == hostSteamId:
					onLobbyClosed()
				elif isHost():
					removeMember_Host(memberId)
			
			MessageType.Member_Reconnected:
				print(memberData[memberId].playerName, " has reconnected")
			
			MessageType.Host_GameStart:
				if partyState == PartyState.Connected and memberId == hostSteamId:
					onStartCountdown()
			
			MessageType.Host_Kicked_Member:
				if memberId == hostSteamId:
					var kickedMemberId = int(split[1])
					if isMe(kickedMemberId):
						onSelfKicked(int(split[2]))
			









			












			
















func onLobbyDataUpdate(success: int, lobbyId, memberId):
	if ignoreLobbyUpdates: return
	
	if memberId == lobbyId:
		
		
		
		
		if isClient():
			
			var sqn = int(getLobbyData(sqnKey, false))
			
			if sqn > metadataSqn:
				metadataSqn = sqn
				
			
				
				onConfigUpdated()
				onGameDataUpdated()
			
			var memberSqn = int(getLobbyData(membersSqnKey, false))
			if memberSqn > memberMetadataSqn:
				memberMetadataSqn = memberSqn
				onMemberListChanged()
	
	else:
		
		
		
		if memberId != SteamHelper.STEAM_ID and memberId in memberData:
			
			var data = memberData.get(memberId, null)
			assert (data != null)
			
			var roundNum = getCurRound()
			if data.getRoundData(roundNum) == null:
				var roundData: String = getLobbyMemberData(memberId, str(roundNum))
				if roundData == READY:
					data.setReady(true)
					emit_signal("update_ready_counter")
					checkAllReady()
				elif roundData == "":
					pass
					
				else:
					data.setReady(false)
					data.addRoundData(roundNum, roundData)
					checkEnterCombat()
			
			var roundResults: String = getLobbyMemberData(memberId, resultsKey)
			if roundResults != "":
				data.setResultsFromString(roundResults)
				recalculateRanking()
				emit_signal("score_changed", memberId)
				
				if Game.curRound >= Game.MAX_ROUNDS_LOBBIES:
					if allOpponentsResultsReceived():
						onOpponentResultsReceived()
		
		if memberId == SteamHelper.STEAM_ID:
			
			makeHostOwner()
			
		
			
		var info = getLobbyMemberData(memberId, memberInfoKey, false)
		if info != "":
			if memberId in memberData:
				updateMemberData(memberId, info)
			
			elif isHost():
				var responseCode = canAddMember(memberId)
				
				if responseCode == ResponseCode.Ok:
					addMember_Host(memberId)
				else:
					print("Cannot add member (", Util.enumToString(ResponseCode, responseCode), ")")
					
					sendKickMessage(memberId, responseCode)
		else:
			Util.eprint("empty info - automatic join/leave/owner change update?")


func makeHostOwner():
	var curOwner = Steam.getLobbyOwner(curLobbyId)
	if not isHost() and curOwner == SteamHelper.STEAM_ID:
		var res = Steam.setLobbyOwner(curLobbyId, hostSteamId)
		print("Host is owner again: ", res)


func startCountdown():
	sendStartCountdownMessage()
	onStartCountdown()
	lobbyTimer.initTimer()
	setRoundAndTimeMetadata(0)
	updateHostUgc()


func onStartCountdown():
	gameHasStarted = true
	ensureTimer()
	emit_signal("start_countdown")

func onGameStart():
	if Game.curMode == Game.Mode.Lobbies:
		ensureScoreboard()

func ensureScoreboard():
	if scoreboardNode == null:
		scoreboardNode = scoreboardScene.instance()
		get_tree().get_root().add_child(scoreboardNode)
		
		scoreboard = scoreboardNode.get_node("Scoreboard")
		
		
		scoreboardButton = scoreboardNode.get_node("LobbyButton")
		

func deleteScoreboard():
	scoreboardNode.queue_free()
	scoreboard.queue_free()
	scoreboardNode = null
	scoreboard = null
	scoreboardButton = null

func ensureTimer():
	if lobbyTimer == null:
		print("create timer")
		lobbyTimer = lobbyTimerScene.instance()
		Game.shopSceneNode.add_child_below_node(Game.startCombatButton, lobbyTimer)

func countReadyMembers() -> int:
	var ready = 0
	for member in memberData:
		if memberData[member].isReady():
			ready += 1
	print(ready, " members ready")
	return ready


func allOpponentsReady() -> bool:
	return countReadyMembers() == getNumMembers()

func allOpponentsSubmitted() -> bool:
	return countReceivedRounds(Game.curRound) == getNumMembers()

func getMissingOpponentNames() -> Array:
	var missing = []
	for memberId in memberList:
		if memberData[memberId].getRoundData(Game.curRound) == null:
			missing.push_back(memberData[memberId].playerName)
	return missing

func allOpponentsResultsReceived() -> bool:
	return countReceivedRoundResults(getCurRound()) == getNumMembers()

func getCurRound() -> int:
	return int(min(Game.curRound, Game.MAX_ROUNDS_LOBBIES))






func canAddMember(_memberId) -> int:
	
	
	
	
	if gameHasStarted:
		return ResponseCode.AlreadyStarted
	
	if getNumMembers() >= getLobbySize():
		return ResponseCode.MemberLimitReached
	
	return ResponseCode.Ok


func addMember_Host(steamId: int, memberUgcIdAsString: String = ""):
	var ugcId = 0
	
	if USE_MEMBER_UGC:
		if memberUgcIdAsString != "":
			ugcId = int(memberUgcIdAsString)
			if ugcId != memberUgcId:
				members.push_back(ugcId)
				if isHost():
					print("host - adding member with id ", memberUgcIdAsString)
					updateHostUgc()
	
	prepareMemberData(steamId, ugcId)
	setMemberListMetadata()

func onMemberListChanged():
	var memberListAsString = getLobbyData(membersKey)
	var newMemberList_String = memberListAsString.split(MSG_DELIMITER)
	var newMemberList = []
	for string in newMemberList_String:
		newMemberList.push_back(int(string))
	
	var newMembers = Util.subtractArr(newMemberList, memberList)
	var removedMembers = Util.subtractArr(memberList, newMemberList)
		
	for memberId in newMembers:
		prepareMemberData(memberId)
	
	for memberId in removedMembers:
		removeMember(memberId)

func prepareMemberData(steamId: int, ugcId = 0):
	
	assert ( not steamId in memberList)
	
	print("adding ", steamId, " to member list")
	
	memberList.push_back(steamId)
	var info: String = getLobbyMemberData(steamId, memberInfoKey)
	






	
	updateMemberData(steamId, info, ugcId)
	
	print("member added successfully")
	emit_signal("member_added", steamId)
	
	if not joinConfirmed and isMe(steamId):
		joinConfirmed = true
		emit_signal("lobby_join_confirmed")

func updateMemberData(steamId, metadata: String, ugcId = 0):
	var data = memberData.get(steamId, null)
	if data == null:
		data = LobbyMemberData.new(steamId, ugcId)
		memberData[steamId] = data
	
	if data.lastMetadata != metadata:
		data.lastMetadata = metadata
		var split = metadata.split(MSG_DELIMITER)
		var playerName = Util.sharedBitstream.deserializeString(split[0])
		var bitStream = BitStream.new()
		bitStream.fromGodotString(split[1])
		var parsedInfo = RunData.deserializeCharacterData(bitStream, true)
		var characterClass = parsedInfo[0]
		var loadout = parsedInfo[1]
		var chibi = parsedInfo[2]
		var skins = parsedInfo[3]
		
		data.setData(playerName, characterClass, loadout, chibi, skins)

func removeMember_Host(steamId: int):
	removeMember(steamId)
	
	
	setMemberListMetadata()
	
func removeMember(steamId: int):
	if not steamId in memberData:
		
		return
	memberData.erase(steamId)
	memberList.erase(steamId)
	onMemberRemoved(steamId)
	checkEnterCombat()

func onMemberRemoved(steamId):
	emit_signal("member_removed", steamId)
	recalculateRanking()
	emit_signal("score_changed")


func kickMember(steamId):
	if not isHost(): return
	sendKickMessage(steamId, ResponseCode.ManualKick)
	removeMember_Host(steamId)

func onSelfKicked(responseCode):
	ignoreLobbyUpdates = true
	emit_signal("kicked", responseCode)
	match responseCode:
		ResponseCode.ManualKick:
			Util.showPopupMessage("ERROR_Kicked")
		ResponseCode.AlreadyStarted:
			Util.showPopupMessage("ERROR_JoinPhaseOver")
		ResponseCode.MemberLimitReached:
			Util.showPopupMessage("ERROR_MemberLimitReached")
	Game.forceLeaveLobby()

func onLobbyClosed():
	if not onResultsScreen:
		ignoreLobbyUpdates = true
		emit_signal("lobby_closed")
		Util.showPopupMessage("ERROR_LobbyClosed")
		Game.forceLeaveLobby()
		


func setLobbyData_sqn(key: String, value: String, _sqnKey: String = sqnKey) -> bool:
	metadataSqn += 1
	setLobbyData(key, value)
	return setLobbyData(_sqnKey, str(metadataSqn), false)


func setLobbyData(key: String, value: String, _print: bool = true) -> bool:
	if _print:
		print("set: ", key, " -> ", value)
	return Steam.setLobbyData(curLobbyId, key, value)

func getLobbyData(key: String, _print: bool = true) -> String:
	var value = Steam.getLobbyData(curLobbyId, key)
	if _print:
		print("get: ", key, " -> ", value)
	return value


func setLobbyMemberData(key: String, value: String, _print: bool = true):
	if _print:
		print("set: ", SteamHelper.STEAM_ID, " key: ", key, " -> ", value)
		
		
		
	Steam.setLobbyMemberData(curLobbyId, key, value)
	
func getLobbyMemberData(playerId: int, key: String, _print: bool = true) -> String:
	var value = Steam.getLobbyMemberData(curLobbyId, playerId, key)
	if _print:
		print("get: ", playerId, " key: ", key, " -> ", value)
		
		
	return value

func onGameDataUpdated():
	var fightTime: String = getLobbyData(nextFightTimeKey)
	if fightTime != "" and lastFightTimestamp != fightTime:
		lastFightTimestamp = fightTime
		
		lobbyTimer.initTimer()
		var split = fightTime.split(MSG_DELIMITER)
		var baseTimestamp = float(split[0])
		var roundDur = float(split[1])
		
		var diff = lobbyTimer.getCurTime() - baseTimestamp
		print("T diff: ", diff)
		
		var fightTimestamp: float
		if reconnecting:
			
			fightTimestamp = baseTimestamp + roundDur
		else:
			fightTimestamp = lobbyTimer.getCurTime() + roundDur - DELAY_COMPENSATION
		
		
		lobbyTimer.updateTimer(fightTimestamp)

func getMemberData(steamId):
	return memberData[steamId]

func getOwnMemberData() -> LobbyMemberData:
	return getMemberData(SteamHelper.STEAM_ID)

func updateOwnMetadata():
	var info = Util.sharedBitstream.serializeString(Game.getPlayerName())
	var bitStream = BitStream.new()
	RunData.serializeCharacterData(bitStream, true)
	info += MSG_DELIMITER + bitStream.toGodotString()
	setLobbyMemberData(memberInfoKey, info)

func updateHostUgc():
	print("updating")
	H_hostUgcMetadata.clear()
	
	H_hostUgcMetadata["id"] = str(SteamHelper.STEAM_ID)
	H_hostUgcMetadata["v"] = getVersionString()
	H_hostUgcMetadata["lobbyId"] = str(curLobbyId)
	if USE_MEMBER_UGC:
		H_hostUgcMetadata["members"] = members
	H_hostUgcMetadata["started"] = gameHasStarted
	var metadataString = to_json(H_hostUgcMetadata)
	ugcItem = UGCItem.new(metadataString, H_hostUgcId)
	ugcItem.connect("item_updated", self, "onHostUgcUpdated")
	add_child(ugcItem)
	ugcItem.update()

func onHostUgcUpdated():
	print("updated")
	pass

func createMessage(type: int, arguments = null):
	if arguments == null:
		return str(type)
	
	if typeof(arguments) == TYPE_ARRAY:
		var stringArgs = PoolStringArray(arguments)
		return str(type) + MSG_DELIMITER + MSG_DELIMITER.join(stringArgs)
	else:
		return str(type) + MSG_DELIMITER + str(arguments)
	






func createAndSendMessage(type: int, arguments = null):
	if ignoreLobbyUpdates: return
	var msg = createMessage(type, arguments)
	sendChatMessage(msg)


func sendJoinMessage():
	createAndSendMessage(MessageType.Member_Joined, [memberUgcId, Game.getPlayerName()])

func sendLeaveMessage():
	createAndSendMessage(MessageType.Member_Left)

func sendReconnectMessage():
	createAndSendMessage(MessageType.Member_Reconnected)

func sendRoundDataMessage(roundNum, metaDataString):
	createAndSendMessage(MessageType.Member_RoundData, [roundNum, metaDataString])

func sendRoundResultMessage(roundNum, result):
	createAndSendMessage(MessageType.Member_RoundResult, [roundNum, result])


func sendStartCountdownMessage():
	createAndSendMessage(MessageType.Host_GameStart)

func sendKickMessage(steamId: int, responseCode: int):
	createAndSendMessage(MessageType.Host_Kicked_Member, [steamId, responseCode])




func resultsToString() -> String:
	var resultsAsString: = ""
	for result in Game.roundResults:
		resultsAsString += str(result)
	return resultsAsString


func collectRoundData():
	for memberId in memberList:
		var data = memberData.get(memberId, null)
		assert (data != null)
		
		var roundNum = Game.curRound
		
		if memberId == SteamHelper.STEAM_ID:
			
			var resultsAsString: = resultsToString()
			setLobbyMemberData(resultsKey, resultsAsString, false)
			data.setResultsFromString(resultsAsString)
			
			
			for roundI in range(1, min(RunDatabase.rounds.size() + 1, roundNum + 1)):
				setLobbyMemberData(str(roundI), RunDatabase.rounds[roundI - 1], false)
				data.addRoundData(roundI, RunDatabase.rounds[roundI - 1])
		else:
			var roundResults: String = getLobbyMemberData(memberId, resultsKey, false)
			if roundResults != "":
				data.setResultsFromString(roundResults)
		
			for roundI in range(1, roundNum + 1):
				var roundData: String = getLobbyMemberData(memberId, str(roundI), false)
				
				if roundData != "":
					if roundI == roundNum and roundData == READY:
						data.setReady(true)
					else:
						
						data.addRoundData(roundI, roundData)
				
				
		
	print("Finished reconnect")
	
	recalculateRanking()
	emit_signal("score_changed")
	
	checkEnterCombat()
	

func countReceivedRounds(forRound):
	var num = 0
	for member in memberData:
		if memberData[member].getRoundData(forRound) != null:
			num += 1
	print(num, " received rounds")
	return num


func onOpponentRoundsReceived():
	
	emit_signal("found_opponent")

func checkAllReady():
	if allOpponentsReady():
		lobbyTimer.forwardTo(2)

func checkEnterCombat():
	
	if allOpponentsSubmitted():
		onOpponentRoundsReceived()

func countReceivedRoundResults(forRound):
	var num = 0
	for member in memberData:
		if memberData[member].getResultOfRound(forRound) != Game.RoundResult.RunOver:
			num += 1
	return num

func onOpponentResultsReceived():
	print("all end results received")
	emit_signal("all_end_results_received")
	ignoreLobbyUpdates = true

var rematchPenalty = [1, 0.7, 0.4, 0.1, 0]
var rematchPenalty_RoundRobin = range(18, 1, - 1)
var rematchPenalty_EvenStats = [3, 2, 1, 0]
var rematchPenalty_Strongest = [0.8, 0.4, 0.2, 0]
var hostRematch = [0, 0, 0, 0, 0.2, 0.4, 0.6, 0.8, 1]


func pickOpponent() -> LobbyMemberData:
	if getNumMembers() == 1:
		return null
	
	var possibleOpponents = []
	for steamId in memberData:
		if steamId != SteamHelper.STEAM_ID:
			var roundData = memberData[steamId].getRoundData(Game.curRound)
			if roundData != null:
				possibleOpponents.push_back(memberData[steamId])
	
	if possibleOpponents.empty():
		Util.eprint("ERR: No opponents")
		return null
	
	if getNumMembers() == 2:
		return possibleOpponents[0]
	
	if prioritizeHost and not isHost():
		
		
		var ago
		var lastMetHost = opponentHistory.find_last(hostSteamId)
		if lastMetHost == - 1:
			ago = opponentHistory.size()
		else:
			ago = Game.curRound - (lastMetHost + 1) - 1
		
		if Util.flip(hostRematch[ago]):
			return getMemberData(hostSteamId)
	
	var minScore: float = 1000000
	var minScoreOpponent = null
	
	for _oppo in possibleOpponents:
		var oppo: LobbyMemberData = _oppo
		var score = 0.0
		
		if opponentHistory.size() >= 2:
			if (oppo.steamId == opponentHistory[ - 1] and 
				oppo.steamId == opponentHistory[ - 2]):
				score += 100
		
		if matchMaking == MatchMaking.Random:
			var noise = [0.5]
			
			score += Util.rng.randf_range(0, Util.getArrayElement(noise, 
				getNumMembers() - 3, noise[ - 1]))
			score += getRematchPenalty(oppo, rematchPenalty)
		
		elif matchMaking == MatchMaking.RoundRobin:
			score += Util.rng.randf_range(0, 0.1)
			score += getRematchPenalty(oppo, rematchPenalty_RoundRobin)
		
		elif matchMaking == MatchMaking.EvenStats:
			score += Util.rng.randf_range(0, 0.1)
			var winDif = oppo.getWinsAtRound(Game.curRound) - Game.getNumWins()
			score += abs(winDif)
			score += getRematchPenalty(oppo, rematchPenalty_EvenStats)
		
		elif matchMaking == MatchMaking.Elimination:
			score += Util.rng.randf_range(0, 0.5)
			score += getRematchPenalty(oppo, rematchPenalty)
			if oppo.getLossesAtRound(Game.curRound) > 5:
				score += 0.5
		
		elif matchMaking == MatchMaking.Strongest:
			score += Util.rng.randf_range(0, 0.1)
			var winRate = oppo.getWinsAtRound(Game.curRound) / float(Game.curRound)
			score += winRate
			score += getRematchPenalty(oppo, rematchPenalty)
		
		if score < minScore:
			minScore = score
			minScoreOpponent = oppo
	
	return minScoreOpponent

func getRematchPenalty(opponentData, penalties: Array) -> float:
	
	var default = Util.getArrayElement(penalties, opponentHistory.size(), penalties[ - 1])
	var lastMatchRound = opponentHistory.find_last(opponentData.steamId)
	if lastMatchRound == - 1:
		return default
	else:
		var ago = Game.curRound - (lastMatchRound + 1) - 1
		return Util.getArrayElement(penalties, ago, default)

func setConfigDefault_Host():
	setLobbyData_sqn(speedConfigKey, String(lobbySpeed))
	setLobbyData_sqn(sizeConfigKey, String(lobbySize))
	setLobbyData_sqn(customRulesConfigKey, customRules)
	setLobbyData_sqn(matchingConfigKey, String(matchMaking))

func onConfigUpdated():
	var changed = false
	
	var speed = int(getLobbyData(speedConfigKey))
	if speed != lobbySpeed:
		changed = true
		setSpeed(speed)
	
	var size = int(getLobbyData(sizeConfigKey))
	if size != lobbySize:
		changed = true
		setLobbySize(size)
	
	var rules = getLobbyData(customRulesConfigKey)
	if rules != customRules:
		changed = true
		setCustomRules(rules)
	
	var matching_encoded = int(getLobbyData(matchingConfigKey))
	var prioritizeH = bool(matching_encoded & MatchMaking.PrioritizeHost)
	var matching = matching_encoded & ( ~ MatchMaking.PrioritizeHost)
	if matching != matchMaking or prioritizeH != prioritizeHost:
		changed = true
		setMatchMaking(matching, prioritizeH)
	
	if changed:
		emit_signal("config_changed")

func getSpeed():
	return lobbySpeed

func setSpeed_Host(speed):
	setSpeed(speed)
	if isInLobby():
		setLobbyData_sqn(speedConfigKey, str(lobbySpeed))
	emit_signal("config_changed")

func setSpeed(speed):
	lobbySpeed = speed
	print("Set Speed to ", lobbySpeed)

func getLobbySize() -> int:
	return lobbySize

func setLobbySize_Host(size: int):
	setLobbySize(size)
	if isInLobby():
		setLobbyData_sqn(sizeConfigKey, str(size))
	emit_signal("config_changed")

func setLobbySize(size: int):
	lobbySize = clamp(size, MIN_MEMBERS, MAX_MEMBERS)
	print("Max. members set to ", lobbySize)

func setCustomRules_Host(rules: String):
	setCustomRules(rules)
	if isInLobby():
		setLobbyData_sqn(customRulesConfigKey, rules)
	emit_signal("config_changed")

func setCustomRules(rules: String):
	customRules = rules
	if rules == "":
		CustomRules.reset()
	else:
		CustomRules.fromString(customRules)

func getMatchmaking() -> int:
	return matchMaking

func getPrioritizeHost() -> bool:
	return prioritizeHost

func setMatchMaking_Host(_matchMaking: int, _prioritizeHost):
	if isInLobby():
		var encoded = _matchMaking
		if _prioritizeHost:
			encoded += MatchMaking.PrioritizeHost
		setLobbyData_sqn(matchingConfigKey, String(encoded))
	setMatchMaking(_matchMaking, _prioritizeHost)
	emit_signal("config_changed")

func setMatchMaking(_matchMaking: int, _prioritizeHost: bool):
	matchMaking = _matchMaking
	prioritizeHost = _prioritizeHost
	print("Matchmaking: ", Util.enumToString(MatchMaking, matchMaking), " - prioritize host: ", prioritizeHost)





func getRoundDuration(roundNum) -> float:
	var shopDur = roundDurationCurve.interpolate((roundNum - 1) / 18.0)
	
	if roundNum == Game.SKILL_ROUND1 or roundNum == Game.SKILL_ROUND2:
		shopDur += 10
	elif roundNum == Game.SUBCLASS_ROUND:
		shopDur += 10
	
	var speedFactor = speedFactors[lobbySpeed]
	shopDur = stepify(shopDur * speedFactor, 1.0)
	
	
	if roundNum == 0:
		
		return shopDur
	if roundNum == Game.MAX_ROUNDS_LOBBIES:
		
		return COMBAT_TIME + 20
	
	
	return shopDur + COMBAT_TIME


func calcRunDuration() -> float:
	var dur = 0.0
	for roundNum in Game.MAX_ROUNDS_LOBBIES:
		dur += getRoundDuration(roundNum)
	return dur

func getRunDuration_Minutes() -> int:
	var totalTime = calcRunDuration()
	return int(round((totalTime + 60) / 60.0))

func getAverageRoundDuration_seconds() -> int:
	var totalTime = calcRunDuration()
	return int(stepify(round(totalTime / 18.0), 5))

func onOwnClassChanged():
	if isInLobby():
		updateOwnMetadata()

func onFightFinished(roundResult: int):
	if isInLobby():
		var resultsAsString: = resultsToString()
		getOwnMemberData().setResultsFromString(resultsAsString)
		
		recalculateRanking()
		emit_signal("score_changed", SteamHelper.STEAM_ID)
		
		
		setLobbyMemberData(resultsKey, resultsAsString)
		
		
		
		if Game.curRound == Game.MAX_ROUNDS_LOBBIES:
			onResultsScreen = true
			deleteScoreboard()
			
			
			if allOpponentsResultsReceived():
				onOpponentResultsReceived()

func getResultScore():
	return getOwnMemberData().getCurrentScore()

func getResultRank():
	return getOwnMemberData().curRanking

func getMemberRanking(steamId):
	return memberData[steamId].curRanking

func recalculateRanking():
	var rankedMembers = memberData.values()
	rankedMembers.sort_custom(MemberSorter, "sort")
	
	var lastRank: = 1
	var iterator: = 1
	var lastScore = - 1
	
	for member in rankedMembers:
		var score = member.getCurrentScore()
		if score == lastScore:
			member.curRanking = lastRank
		else:
			member.curRanking = iterator
			lastRank = iterator
			lastScore = score
			
		iterator += 1


func tryReconnect():
	reconnecting = true
	partyState = PartyState.Reconnecting
	var runState = Game.getRunState(Game.Mode.Lobbies)
	hostSteamId = runState["hostId"]
	curPartyUgcId = runState["ugcId"]
	joinLobby(runState["lobbyId"])

const MSG_DELIMITER = ","

const symbols = [
	"a", "b", "c", "d", 
	"f", "g", "h", "j", 
	"k", "l", "m", "n", "p", 
	"q", "r", "s", "t", "u", 
	"v", "w", "x", "y", "z", 
	"1", "2", "3", "4", "5", 
	"6", "7", "8", "9"
]

onready var symbolDict = Util.arrayAsIndexDict(symbols)
























class MemberSorter:
	static func sort(member1: LobbyMemberData, member2: LobbyMemberData):
		return member1.getCurrentScore() > member2.getCurrentScore()


